// -*- C++ -*-
//
// Package:    GEMFedRawProducerV2
// Class:      GEMFedRawProducerV2
// 
/**\class GEMFedRawProducerV2 GEMFedRawProducerV2.cc work/GEMFedRawProducerV2/plugins/GEMFedRawProducerV2.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/


// system include files
#include <memory>
#include <iomanip> 
#include <iostream>
#include <fstream>
#include <vector>
#include <inttypes.h>

#include "EventFilter/GEMRawToDigi/interface/GEMAMC13EventFormat.h"
#include "EventFilter/GEMRawToDigi/interface/GEMDataAMCformat.h"
#include "EventFilter/GEMRawToDigi/interface/GEMslotContents.h"
#include "EventFilter/GEMRawToDigi/interface/GEMDataChecker.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"

#include "DataFormats/GEMDigi/interface/GEMDigiCollection.h"

//
// class declaration
//

class GEMFedRawProducerV2 : public edm::EDProducer {
        public:
                explicit GEMFedRawProducerV2(const edm::ParameterSet&);
                ~GEMFedRawProducerV2();

                static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

        private:
                virtual void beginJob() override;
                virtual void produce(edm::Event&, const edm::EventSetup&) override;
                virtual void endJob() override;

                virtual void ByteVector(std::vector<unsigned char>&, uint64_t&);

                int GetStripFromChannel(uint16_t ChipID, int chan);  
                int GetIEtaFromChipID(uint16_t ChipID);

                //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
                //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
                //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
                //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

                // ----------member data ---------------------------

                std::string inputFileName_;// = "GEMDQMRawData.dat";
                std::ifstream inpf_;

                std::vector<int> slotVector_;
                bool checkQualityEvent_;
                bool verbose_;
                std::string FedKit_;

                uint64_t m_word;
                uint32_t m_word32;
                bool type;
                AMC13Event * m_AMC13Event;
                std::FILE *m_file;

                uint16_t nBC;


};

//
// constants, enums and typedefs
//
typedef GEMDataAMCformat::GEMData  AMCGEMData;
typedef GEMDataAMCformat::GEBData  AMCGEBData;
typedef GEMDataAMCformat::VFATData AMCVFATData;

//
// static data member definitions
//

//
// constructors and destructor
//
GEMFedRawProducerV2::GEMFedRawProducerV2(const edm::ParameterSet& iConfig)
{
        //register your products if do put with a label
        produces<FEDRawDataCollection>("GEMTBData");
        produces<GEMDigiCollection>();

        inputFileName_ = iConfig.getParameter<std::string>("inputFileName");

        // GEM Raw Data file
        std::ifstream inpf_(inputFileName_.c_str(), std::ios::in|std::ios::binary);
        m_file = std::fopen(inputFileName_.c_str(), "rb");

        FedKit_ = iConfig.getUntrackedParameter<std::string>("FedKit","sdram"); 
        slotVector_ = iConfig.getParameter<std::vector<int> >("slotVector");    
        verbose_ = iConfig.getUntrackedParameter<bool >("verbose",false);
        checkQualityEvent_ = iConfig.getUntrackedParameter<bool>("checkQualityEvent",true);

}


GEMFedRawProducerV2::~GEMFedRawProducerV2()
{
        // do anything here that needs to be done at desctruction time
        // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called once each job just before starting event loop  ------------
        void 
GEMFedRawProducerV2::beginJob()
{

        // Checking of Hex/binary type
        //char c = inpf_.get();
        inpf_.close();
        inpf_.open(inputFileName_.c_str(), std::ios::in|std::ios::binary);
        if(!inpf_.is_open()) {
                edm::LogError("") << "\nThe GEM file: " << inputFileName_.c_str() << " is missing.\n";
        };



}


// ------------ method called to produce the data  ------------
        void
GEMFedRawProducerV2::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
        using namespace edm;

        AMCGEMData  gem;
        AMCGEBData  geb;
        AMCVFATData vfat;

        //uint64_t ui64bits = 0;

        std::auto_ptr<FEDRawDataCollection> pOut(new FEDRawDataCollection());
        std::auto_ptr<GEMDigiCollection> producedGEMDigis(new GEMDigiCollection);

        if(inpf_.eof()) { iEvent.put(pOut,"GEMTBData");   return; } // We should put out a collection even if it is empty
        if(!inpf_.good()) { iEvent.put(pOut,"GEMTBData");  return; }

        std::vector<unsigned char> byteVec;  

        // read and print FEROL headers
        if (FedKit_ == "ferol") {
                std::size_t sz = std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                if (sz == 0 ) return;
                if(verbose_) printf("%016lX\n", m_word);
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                if(verbose_)  printf("%016lX\n", m_word);
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                if(verbose_)  printf("%016lX\n", m_word);
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                // ferol headers read and printed, now read CDF header
                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                if(verbose_)  printf("%016lX\n", m_word);
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);

        } else {
                std::size_t sz = std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                if (sz == 0 ) return;
        }

        // read and print "BADC0FFEEBADCAFE" and another artificial header
        if(verbose_)  printf("%016lX\n", m_word);
        m_AMC13Event = new AMC13Event();
        m_AMC13Event->setCDFHeader(m_word);
        std::fread(&m_word, sizeof(uint64_t), 1, m_file);
        if(verbose_)  printf("%016lX\n", m_word);
        GEMFedRawProducerV2::ByteVector(byteVec, m_word);
        m_AMC13Event->setAMC13header(m_word);
        if(verbose_)  std::cout << "n_AMC = " << m_AMC13Event->nAMC() << std::endl;

        // Readout out AMC headers
        for (unsigned short i = 0; i < m_AMC13Event->nAMC(); i++){
                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                if(verbose_)  printf("%016lX\n", m_word);
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                m_AMC13Event->addAMCheader(m_word);
        }
        // Readout out AMC payloads
        for (unsigned short i = 0; i < m_AMC13Event->nAMC(); i++){
                AMCdata * m_amcdata = new AMCdata();
                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                if(verbose_)  {
                        printf("AMC HEADER1\n");
                        printf("%016lX\n", m_word);}
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                m_amcdata->setAMCheader1(m_word);
                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                if(verbose_)  {printf("AMC HEADER2\n");
                        printf("%016lX\n", m_word);}
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                m_amcdata->setAMCheader2(m_word);
                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                m_amcdata->setGEMeventHeader(m_word);
                if(verbose_)  {printf("GEM EVENT HEADER\n");
                        printf("%016lX\n", m_word);}
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                if(verbose_)  std::cout<<"  --->"<<m_amcdata->BX()<<"   "<<m_amcdata->BID()<<std::endl;

                // fill the geb data here
                for (unsigned short j = 0; j < m_amcdata->GDcount(); j++){
                        GEBdata * m_gebdata = new GEBdata();
                        std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                        m_gebdata->setChamberHeader(m_word);
                        if(verbose_)   {printf("GEM CHAMBER HEADER\n");
                                printf("%016lX\n", m_word);} 
                        GEMFedRawProducerV2::ByteVector(byteVec, m_word);

                        // fill the vfat data here
                        if(verbose_)  std::cout << "Number of VFAT words " << m_gebdata->Vwh() << std::endl;
                        int m_nvb = m_gebdata->Vwh() / 3; // number of VFAT2 blocks. Eventually add here sanity check
                        if(verbose_)  std::cout << "Number of VFAT blocks " << m_nvb << std::endl;

                        for (unsigned short k = 0; k < m_nvb; k++){
                                VFATdata * m_vfatdata = new VFATdata();
                                // read 3 vfat block words, totaly 192 bits
                                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                                if(verbose_){
                                        printf("VFAT WORD 1\n");
                                        printf("%016lX\n", m_word);
                                }
                                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                                m_vfatdata->read_fw(m_word);
                                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                                if(verbose_){
                                        printf("VFAT WORD 2\n");
                                        printf("%016lX\n", m_word);
                                }
                                m_vfatdata->read_sw(m_word);
                                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                                if(verbose_){
                                        printf("VFAT WORD 3\n");
                                        printf("%016lX\n", m_word);
                                }
                                m_vfatdata->read_tw(m_word);
                                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                                //
                                if(verbose_){
                                        printf("VFAT MS Data 3\n");
                                        printf("%016lX\n", m_vfatdata->msData());
                                        printf("VFAT LS Data 3\n");
                                        printf("%016lX\n", m_vfatdata->lsData());
                                }
                                m_gebdata->v_add(*m_vfatdata);

                                uint16_t bc=m_vfatdata->BC();
                                uint8_t ec=m_vfatdata->EC();
                                uint8_t b1010=m_vfatdata->b1010();
                                uint8_t b1100=m_vfatdata->b1100();
                                uint8_t b1110=m_vfatdata->b1110();
                                uint16_t  ChipID=m_vfatdata->ChipID();

                                bool Quality = (b1010==10) && (b1100==12) && (b1110==14) ;      // add CRC? 

                                if(verbose_){
                                        std::cout<<" ---> VFAT--->"<<(unsigned)bc<<" -   "<<(unsigned)ec<<" -   "<<(unsigned)ChipID<<std::endl;
                                        std::cout<<" -->"<<(unsigned)b1010<<"    "<<(unsigned)b1100<<"    "<<(unsigned)b1110<<std::endl;
                                }

                                if(!Quality && checkQualityEvent_) continue;


                                int etaP=GetIEtaFromChipID(ChipID);

                                int chamberPosition=1; // this depends on chamberID (DB again) 
                                int schamberPosition=1; // this depends on chamberID  (DB again)

                                int bx=0;  
                                uint8_t chan0xf = 0;
                                for(int chan = 0; chan < 128; ++chan) {
                                        if(chan < 64){
                                                chan0xf = ((vfat.lsData >> chan) & 0x1);
                                        } else {
                                                chan0xf = ((vfat.msData >> (chan-64)) & 0x1);
                                        }
                                        if (chan0xf != 0) {
                                                if(verbose_) std::cout<<"----------->"<<chan<<"   "<<(unsigned)chan0xf<<std::endl;
                                                int strip=GetStripFromChannel(ChipID,chan);  
                                                // This is not correct, the strip needs to be mapped to the channel depending on ChipID&chan -> to be done with a DB  
                                                GEMDigi digi(strip,bx); 
                                                // this is a single digi, where we should give 
                                                // in input the strip and bx relative to trigger that is always 0 for VFAT2 --> To be fixed! 
                                                producedGEMDigis.get()->insertDigi(GEMDetId(1,1,1,schamberPosition,chamberPosition,etaP),digi); 

                                        }
                                }
                                delete m_vfatdata;

                        }
                        std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                        GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                        m_gebdata->setChamberTrailer(m_word);
                        m_amcdata->g_add(*m_gebdata);
                        delete m_gebdata;
                }
                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                m_amcdata->setGEMeventTrailer(m_word);
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                std::fread(&m_word, sizeof(uint64_t), 1, m_file);
                GEMFedRawProducerV2::ByteVector(byteVec, m_word);
                if(verbose_){
                        printf("AMC TRALIER\n");
                        printf("%016lX\n", m_word);
                }
                m_amcdata->setAMCTrailer(m_word);
                m_AMC13Event->addAMCpayload(*m_amcdata);
                delete m_amcdata;
        }
        std::fread(&m_word, sizeof(uint64_t), 1, m_file);
        m_AMC13Event->setAMC13trailer(m_word);
        GEMFedRawProducerV2::ByteVector(byteVec, m_word);
        std::fread(&m_word, sizeof(uint64_t), 1, m_file);
        m_AMC13Event->setCDFTrailer(m_word);
        GEMFedRawProducerV2::ByteVector(byteVec, m_word);


        uint64_t OneEventBytes = byteVec.size();

        if (OneEventBytes> 0 ) 
        {
                FEDRawData f1(OneEventBytes); // One Event has been allocated

                for (uint64_t i=0; i<OneEventBytes; i++){
                        f1.data()[i] = byteVec[i];
                }

                //     std::auto_ptr<FEDRawDataCollection> pOut(new FEDRawDataCollection());
                pOut->FEDData(999) = f1;
                //     iEvent.put(pOut,"GEMTBData");

        }

        if(verbose_) std::cout <<" Run "<< iEvent.eventAuxiliary().run()<<"     "<<iEvent.eventAuxiliary().event()<<std::endl;
        iEvent.put(pOut,"GEMTBData"); iEvent.put(producedGEMDigis);
}

// ------------ method called once each 64 Bits data word and keep in vector ------------
void 
GEMFedRawProducerV2::ByteVector(std::vector<unsigned char>& byteVec, uint64_t& word64ui) {

        union{uint64_t ui64; unsigned char byte[8];} U;

        U.ui64 = word64ui;
        for (int iChar=0; iChar<8; ++iChar){
                byteVec.push_back(U.byte[iChar]);  
        }
        //std::cout << " word64ui 0x" << std::hex << U.ui64 << std::dec << " byteVec.size() " << byteVec.size() << std::endl; 

}


// ------------ method called once each job just after ending the event loop  ------------
void 
GEMFedRawProducerV2::endJob() {
        // Data GEM Stream close
        inpf_.close();
}

// ------------ method called when starting to processes a run  ------------
/*
   void
   GEMFedRawProducerV2::beginRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void
   GEMFedRawProducerV2::endRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void
   GEMFedRawProducerV2::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void
   GEMFedRawProducerV2::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GEMFedRawProducerV2::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
        //The following says we do not know what parameters are allowed so do no validation
        // Please change this to state exactly what you do use, even if it is no parameters
        edm::ParameterSetDescription desc;
        desc.setUnknown();
        descriptions.addDefault(desc);
}

int 
GEMFedRawProducerV2::GetIEtaFromChipID(uint16_t ChipID){

        int etaP=0;

        // This needs to be replaced! to be read from the DB
        for (unsigned int i=0; i<slotVector_.size(); i++) {
                if( (ChipID&0x0fff) == slotVector_.at(i)) {
                        etaP=i%8;
                        if(verbose_) std::cout<<"-----> SLOT "<<i<<"   "<<etaP<<std::endl;;
                }}

        return etaP;   // To be fixed reading from the DB

};

int 
GEMFedRawProducerV2::GetStripFromChannel(uint16_t ChipID, int chan){

        return chan;   // To be fixed reading from the DB

};

//define this as a plug-in
DEFINE_FWK_MODULE(GEMFedRawProducerV2);

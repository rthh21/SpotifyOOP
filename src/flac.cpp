#include "flac.hpp"

FLAC::FLAC() : compression(0) {}
explicit FLAC::FLAC(int compression) : compression(compression) {}
virtual FLAC::~FLAC() {}

void play() const override{
    std::cout<< "Playing flac file from "<< PATH <<" with compression level: "<< compression <<std::endl;
    
}
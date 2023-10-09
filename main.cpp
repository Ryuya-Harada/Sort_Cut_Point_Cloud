#include "include/config.h"
#include "include/process.hpp"

int main(int argc, char **argv){
    auto cfg = SCPC::Config(argc, argv);
    
    for ( const auto& file : cfg.files )
        SCPC::Process(file, cfg.cut, cfg.sort);
}
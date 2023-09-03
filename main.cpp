#include "include/config.h"
#include "include/read.h"
#include "include/write.h"

int main(int argc, char **argv){
    auto cfg = SCPC::Config(argc, argv);
    
    for ( const auto& file : cfg.files )
    {
        auto ply = SCPC::PolygonFileFormat(file);
        ply.Read();
        if ( cfg.sort ) ply.Sort();
        if ( cfg.cut ) ply.Cut();
        ply.Write();
    }
}
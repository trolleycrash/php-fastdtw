#include <iostream>
#include <phpcpp.h>
#include "FastDTW-x/FastDTW-x/Classes/DTW.h"
#include "FastDTW-x/FastDTW-x/Classes/FastDTW.h"
#include "FastDTW-x/FastDTW-x/Classes/EuclideanDistance.h"
#include "FastDTW-x/FastDTW-x/Classes/TimeSeries.h"
#include "FastDTW-x/FastDTW-x/Classes/TimeSeriesPoint.h"
#include "FastDTW-x/FastDTW-x/Classes/TimeWarpInfo.h"


Php::Value dtw(Php::Parameters &params) {
	fastdtw::TimeSeries<double,1> tsI;

    for (int i = 0; i<params[0].size(); ++i) {
        double value = params[0][i];
        tsI.addLast(i, fastdtw::TimeSeriesPoint<double,1>(&value));
    }

    fastdtw::TimeSeries<double,1> tsJ;
    for (int i = 0;i<params[1].size(); ++i)
    {
        double value = params[1][i];
        tsJ.addLast(i, fastdtw::TimeSeriesPoint<double,1>(&value));
    }

    fastdtw::TimeWarpInfo<double> info =  fastdtw::FAST::getWarpInfoBetween(tsI,tsJ,fastdtw::EuclideanDistance());

    return info.getDistance();
 }

Php::Value slowdtw(Php::Parameters &params) {
	fastdtw::TimeSeries<double,1> tsI;

    for (int i = 0; i<params[0].size(); ++i) {
        double value = params[0][i];
        tsI.addLast(i, fastdtw::TimeSeriesPoint<double,1>(&value));
    }

    fastdtw::TimeSeries<double,1> tsJ;
    for (int i = 0;i<params[1].size(); ++i)
    {
        double value = params[1][i];
        tsJ.addLast(i, fastdtw::TimeSeriesPoint<double,1>(&value));
    }

    fastdtw::TimeWarpInfo<double> info =  fastdtw::STRI::getWarpInfoBetween(tsI,tsJ,fastdtw::EuclideanDistance());

    return info.getDistance();
 }




/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("php-fastdtw", "0.1");

        extension.add("dtw", slowdtw, {
            Php::ByVal("series1", Php::Type::Array),
            Php::ByVal("series2", Php::Type::Array)
        });

        extension.add("fastdtw", dtw, {
            Php::ByVal("series1", Php::Type::Array),
            Php::ByVal("series2", Php::Type::Array)
        });

        
        // return the extension
        return extension;
    }
}

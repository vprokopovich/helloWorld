#ifndef EXAMPLEPROGRAMOPTIONS_H
#define EXAMPLEPROGRAMOPTIONS_H

#include "ExampleBase.h"
#include <boost/program_options.hpp>

using namespace std;

namespace po = boost::program_options;

class ExampleProgramOptions : public ExampleBase
{
public:
	ExampleProgramOptions(int argc, char** argv)
    : mArgc(argc)
    , mArgv(argv)
    {

    }
    void run()
	{
		/*
        po::options_description desc("ExampleProgramOptions options");
        desc.addOptions()
            ("help", "print info");
        */
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help, h", "produce help message")
            ("filename, f", po::value<string>(&mOptionFilename)->default_value("default.txt"), "Filename")
            ("command, c", po::value<string>(&mOptionCommand)->default_value("someCommand"), "Specify some command")
            ;

        po::variables_map vm;
        auto parsed = po::parse_command_line(mArgc, mArgv, desc);
        po::store(parsed, vm);
        po::notify(vm);

        processHelpOption(desc, vm);
        processFilenameOption(desc, vm);
        processFilenameCommand(desc, vm);

        

	}
private:
    void processHelpOption(const po::options_description& desc, const po::variables_map& vm)
    {
        if (vm.count("help") > 0)
        {
            cout << desc << endl;
        }
    }
    void processFilenameOption(const po::options_description& desc, const po::variables_map& vm)
    {
        cout << "Processing file: " << /*vm["filename"].as<string>()*/mOptionFilename << endl;
    }
    void processFilenameCommand(const po::options_description& desc, const po::variables_map& vm)
    {
        cout << "Processing command: " << /*vm["filename"].as<string>()*/mOptionCommand << endl;
    }

    int mArgc;
    char** mArgv;

    string mOptionFilename;
    string mOptionCommand;
};

#endif // EXAMPLEPROGRAMOPTIONS_H
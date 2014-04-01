#include "DriverArguments.h"
#include <stdio.h>    /* For fprintf, stderr */
#include <stdlib.h>   /* For atoi, exit */
#include <string.h>   /* For strcmp */
#include <stdarg.h>   /* For va_list, va_args */
#include <time.h>     /* For time */

namespace MFM { 

  void DriverArguments::Die(const char * format, ...) {
    fprintf(stderr,"ERROR: ");
    va_list ap;
    va_start(ap,format);
    vfprintf(stderr, format, ap);
    fprintf(stderr, "\n");
    exit(1);
  }

  static char * GetNextArg(int & count, char ** & argv) {
    if (count <= 0) 
      return 0;
    --count;
    return *argv++;
  }

  /* This should be written with getopt! */
  int DriverArguments::ProcessArguments(int argc, char **argv) 
  {
    m_programName = GetNextArg(argc,argv);

    if (!m_programName)
      Die("Missing program name?");

    while (argc > 0) {
      const char * arg = GetNextArg(argc,argv);
      if (!arg) Die("Unreachable?");
        
      if (!strcmp("-s",arg) || !strcmp("--seed",arg)) {

        const char * val = GetNextArg(argc,argv);
        if (!val) Die("Missing seed (integer) argument after %s", arg);

        m_seed = atoi(val);
        fprintf(stderr,"[Seed %d]\n",m_seed);

      } else if (!strcmp("-e",arg) || !strcmp("--events",arg)) {

        const char * val = GetNextArg(argc,argv);
        if (!val) Die("Missing aeps (integer) argument after %s", arg);

        m_recordEventCountsPerAEPS = atoi(val);
        fprintf(stderr,"[Recording event counts approximately every %d AEPS]\n",m_recordEventCountsPerAEPS);

      } else if (!strcmp("-d",arg) || !strcmp("--dir",arg)) {

        const char * val = GetNextArg(argc,argv);
        if (!val) Die("Missing aeps (integer) argument after %s", arg);

        m_dataDirPath = val;
        fprintf(stderr,"[Data directory path = %s]\n",m_dataDirPath);

      } else if (!strcmp("-p",arg) || !strcmp("--pictures",arg)) {

        const char * val = GetNextArg(argc,argv);
        if (!val) Die("Missing aeps (integer) argument after %s", arg);

        m_recordScreenshotPerAEPS = atoi(val);
        m_recordScreenshotPerAEPS = atoi(val);
        fprintf(stderr,"[Recording grid pictures approximately every %d AEPS]\n",m_recordScreenshotPerAEPS);

      } else if (!strcmp("--picturesPerRate",arg)) {

        const char * val = GetNextArg(argc,argv);
        if (!val) Die("Missing COUNT (integer) argument after %s", arg);

        m_countOfScreenshotsPerRate = atoi(val);
        if (m_countOfScreenshotsPerRate < 1) Die("COUNT must be greater than zero, after %s",arg);
        fprintf(stderr,"[Accelerating in groups of %d pictures]\n",m_countOfScreenshotsPerRate);

      }

      else if (!strcmp("--haltafteraeps", arg))
      {
	const char* val = GetNextArg(argc, argv);
	if(!val) Die("Missing aeps (integer) argument after %s", arg);

	m_haltAfterAEPS = atoi(val);
	if(m_haltAfterAEPS > 0)
	{
	  fprintf(stderr, "[Halting execution after approximately %d AEPS]\n", m_haltAfterAEPS);
	}
      }

      else if (!strcmp("--startpaused", arg) || !strcmp("--nostartpaused", arg))
      {
	m_startPaused = !strcmp("--startpaused", arg);
        if (m_startPaused)
        {
          fprintf(stderr, "[Starting paused]\n");
        } else {
          fprintf(stderr, "[Starting without initial pause]\n");
        } 
      }

      else if (!strcmp("-h",arg) || !strcmp("--help",arg)) {

        fprintf(stderr,
                "Arguments arg:\n"
                " -h, --help                 Print this help\n"
                " -s NUM, --seed NUM         Set master PRNG seed to NUM (u32)\n"
                " -d DIR, --dir DIR          Store data in per-sim directories under DIR\n"
                " -e AEPS, --events AEPS     Record event counts every AEPS aeps\n"
                " -p AEPS, --pictures AEPS   Record screenshots every AEPS aeps\n"
		"\n"
                " --picturesPerRate COUNT    Take COUNT shots per speed from 1 up to -p value\n"
		" --haltafteraeps AEPS       If AEPS > 0, Halts after AEPS elapsed aeps.\n"
		" --startpaused              Start paused to allow display configuration.\n"
		" --nostartpaused            Start running immediately for hands-off operation.\n"
                );
        exit(0);
      } else {
        Die("Unrecognized argument '%s', try '%s -h' for help", 
            arg, m_programName);
      }
    }
    return 0;
  }

}


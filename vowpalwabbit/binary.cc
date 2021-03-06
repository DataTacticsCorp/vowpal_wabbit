#include "oaa.h"
#include "vw.h"

namespace BINARY {
  void learn(void* d, learner& base, example* ec)
  {
    base.learn(ec);
    
    float prediction = -1;
    if ( ec->final_prediction > 0)
      prediction = 1;
    ec->final_prediction = prediction;
  }

  learner* setup(vw& all, std::vector<std::string>&opts, po::variables_map& vm, po::variables_map& vm_file)
  {
    if (!vm_file.count("binary")) 
      {
	std::stringstream ss;
	ss << " --binary ";
	all.options_from_file.append(ss.str());
      }

    all.sd->binary_label = true;

    learner* l = new learner(NULL, learn, all.l);

    l->set_finish_example(OAA::finish_example);
    return l;
  }
}

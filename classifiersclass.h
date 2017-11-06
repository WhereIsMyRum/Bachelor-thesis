#ifndef CLASSIFIERSCLASS_H
#define CLASSIFIERSCLASS_H

#include <QObject>
#include <QVector>
#include <dlib/svm.h>

typedef dlib::matrix<double,8,1> sample_type;
typedef dlib::radial_basis_kernel<sample_type> kernel_type;
typedef dlib::decision_function<kernel_type> dec_funct_type;
typedef dlib::normalized_function<dec_funct_type> funct_type;
//typedef dlib::probabilistic_decision_function<kernel_type> probabilistic_funct_type;
//rtypedef dlib::normalized_function<probabilistic_funct_type> pfunct_type;

class classifiersClass
{
public:

    classifiersClass();

private:

    //needed for krr
    std::vector<sample_type> samples;
    std::vector<double> labels;
    sample_type samp;
    const double gamma = 3.0; // 3.0/dlib::compute_mean_squared_distance(samples)
    dlib::krr_trainer<kernel_type> trainer;

    //needed for svm
    dlib::vector_normalizer<sample_type> normalizer;
    //dlib::svm_c_trainer<kernel_type> trainer;
};

#endif // CLASSIFIERSCLASS_H

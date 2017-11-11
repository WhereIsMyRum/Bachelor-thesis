#ifndef CLASSIFIERSCLASS_H
#define CLASSIFIERSCLASS_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <dlib/svm.h>

typedef dlib::matrix<double,8,1> sample_type;
typedef dlib::radial_basis_kernel<sample_type> kernel_type;

typedef dlib::decision_function<kernel_type> dec_funct_type;
typedef dlib::normalized_function<dec_funct_type> funct_type;

class ClassifiersClass
{
public:

    ClassifiersClass(const std::vector<sample_type>& dataVector, const std::vector<double>& dataLabels);
    bool classifySignalUsingSVM(sample_type &sampleDataMatrix);
    bool classifySignalUsingKRR(sample_type &sampleDataMatrix);

private:

    dlib::vector_normalizer<sample_type> normalizer;

    //needed for krr
    dlib::vector_normalizer<sample_type> krr_normalizer;
    dlib::krr_trainer<kernel_type> krr_trainer;
    funct_type krr_decision_function;

    //needed for svm
    dlib::svm_c_trainer<kernel_type> svm_trainer;
    funct_type svm_decision_function;

    void normalizeSamples(std::vector<sample_type>&);


};

#endif // CLASSIFIERSCLASS_H

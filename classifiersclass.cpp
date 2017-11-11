#include "classifiersclass.h"

ClassifiersClass::ClassifiersClass(const std::vector<sample_type>& dataVector, const std::vector<double>& dataLabels)
{
    std::vector<sample_type> tempDataVector = dataVector;

    normalizer.train(tempDataVector);
    normalizeSamples(tempDataVector);

    /*for(double gamma = 0.00001; gamma <= 1; gamma *= 5)
    {
        for(double C = 1; C < 100000; C *= 5)
        {
            svm_trainer.set_kernel(kernel_type(gamma));
            svm_trainer.set_c(C);

            std::cout << "gamma: " << gamma << "      C: " << C;
            std::cout << "\ncross validation accuracy: " << dlib::cross_validate_svm_trainer(svm_trainer,tempDataVector,dataLabels,3);
        }
    }*/

    svm_trainer.set_kernel(kernel_type(0.00125));
    svm_trainer.set_c(78125);

    svm_decision_function.normalizer = normalizer;
    svm_decision_function.function = svm_trainer.train(tempDataVector,dataLabels);

    //qDebug() << "\nnumber of support vector in learned_functions is: " << learned_function.function.basis_vectors.size() << "\n";

    krr_trainer.use_classification_loss_for_loo_cv();

    /*for(double gamma =0.000001; gamma<=1; gamma *= 5)
    {
        krr_trainer.set_kernel(kernel_type(gamma));

        std::vector<double> loo_values;
        krr_trainer.train(tempDataVector,dataLabels,loo_values);
        const double classification_accuracy = dlib::mean_sign_agreement(dataLabels,loo_values);
        qDebug() <<"gamma: " << gamma << "   LOO accuracy: " <<classification_accuracy;
    }*/

    krr_trainer.set_kernel(kernel_type(0.000625));

    krr_decision_function.normalizer = normalizer;
    krr_decision_function.function = krr_trainer.train(tempDataVector,dataLabels);

    //std::cout << "\nnumberof basis vectors in our learned function is " << krr_decision_function.function.basis_vectors.size() << "\n";
}

void ClassifiersClass::normalizeSamples(std::vector<sample_type> &dataVector)
{
    for(unsigned int i = 0; i < dataVector.size(); i++)
    {
        dataVector.at(i) = normalizer(dataVector.at(i));
    }
}

bool ClassifiersClass::classifySignalUsingSVM(sample_type &sampleDataMatrix)
{
    if(svm_decision_function(sampleDataMatrix) > 0) return true;
    else return false;
}

bool ClassifiersClass::classifySignalUsingKRR(sample_type &sampleDataMatrix)
{
    if(krr_decision_function(sampleDataMatrix) > 0) return true;
    else return false;

}

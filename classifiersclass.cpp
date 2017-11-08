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
            trainer.set_kernel(kernel_type(gamma));
            trainer.set_c(C);

            std::cout << "gamma: " << gamma << "      C: " << C;
            std::cout << "\ncross validation accuracy: " << dlib::cross_validate_trainer(trainer,tempDataVector,dataLabels,3);
        }
    }*/

    trainer.set_kernel(kernel_type(0.00125));
    trainer.set_c(78125);

    learned_function.normalizer = normalizer;
    learned_function.function = trainer.train(tempDataVector,dataLabels);

    //std::cout << "\nnumber of support vector in learned_functions is: " << learned_function.function.basis_vectors.size() << endl;

}

void ClassifiersClass::normalizeSamples(std::vector<sample_type> &dataVector)
{
    for(unsigned int i = 0; i < dataVector.size(); i++)
    {
        dataVector.at(i) = normalizer(dataVector.at(i));
    }
}

bool ClassifiersClass::classifySignal(sample_type &sampleDataMatrix)
{
    if(learned_function(sampleDataMatrix) > 0) return true;
    else return false;
}

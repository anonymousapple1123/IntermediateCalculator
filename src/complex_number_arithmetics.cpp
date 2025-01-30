#include <iostream>
#include <type_traits>
#include <vector>
//#added  comments
template<typename T, typename Enable = void>
class ComplexNumber;

template<typename T>
class ComplexNumber<T, typename std::enable_if<std::is_floating_point<T>::value && std::is_signed<T>::value>::type> {
	private:
	T real_1;
	T real_2;
	T imaginary_1;
	T imaginary_2;
public:
ComplexNumber(T real_1, T imaginary_1, T real_2,  T imaginary_2){
	this->real_1=real_1;
	this->real_2=real_2;
	this->imaginary_1=imaginary_1;
	this->imaginary_2=imaginary_2;
	//std::cout<<"Constructor called successfully";
}

std::vector<T> AddComplexNumber(){
	std::vector<T> result;
   // std::cout<<real_1+real_2<<" + i"<<imaginary_1+imaginary_2;
	result.push_back(real_1+real_2);
	result.push_back(imaginary_1+imaginary_2);
	return result;
}
std::vector<T> SubtractComplexNumber(){
 	//std::cout<<real_1-real_2<<" + i"<<imaginary_1-imaginary_2;
	std::vector<T> result;
	result.push_back(real_1-real_2);
	result.push_back(imaginary_1-imaginary_2);	
	return result;
}


};

int main(){
std::cout<<"_____________________________________________________PROGRAM STARTED................................................"<<std::endl;
//std::cout<<"Enter first number :_"<<std::endl;
//std::cin>>r_1,i_1;
//std::cin>>r_2,i_2;
ComplexNumber<double> num1(1.0,9.0,4.0,1.0);
	
std::vector <double> array = num1.AddComplexNumber();

std::cout<<"Resulatant vecctor "<<array[0]<<"  i"<<array[1]<<std::endl;
return 0;
}


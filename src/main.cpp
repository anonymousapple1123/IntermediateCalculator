#include<iostream>
#include"complex_number_arithmetics.cpp"

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

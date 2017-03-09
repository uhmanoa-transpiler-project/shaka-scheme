#include <vector>
#include <iostream>

namespace shaka{

class String{
public:
    //make new string with length "size" 
    String(long long int size){  
        a_string.resize(size);
    }

    //Create char vector with size "size" and initialize with character "b""
    String(long long int size, char b){

        for(long long int i = 0 ; i < size; i++){
            a_string.push_back(b); 
        }
    }

    //Makes a copy of a string
    String(String &c){
        for (long long int i = 0; i < c.getString().size(); i++){
            a_string[i] = c.getString()[i];
            } 
    }

    String(String &c, long long int index1, long long int index2){

        for(long long int i=index1; i <= index2; i++){
            a_string[i] = c.getString()[i];
        }

    }

    //return length of a_string
    long long int string_length(){
        return a_string.size();
    }

    //takes the index, and returns the value of the index
    char string_ref(long long int index){

        for(int i = 0; i < a_string.size(); i++){
            if (i == index){
                return a_string[index];
            }
        }
        return 'e';
    }

    void string_set(long long int index, char a){

        for(int i = 0; i < a_string.size(); i++){
            if (i == index){
                a_string[index] = a;
            }
        }
    }

//Need to make it case insensitive     
    bool string_equal(String &s1, String &s2){

        if(s1.getString().size() != s2.getString().size()){
            return false;
        }
        for(long long int i = 0; i < s1.getString().size(); i++){

            if(s1.getString()[i] != s2.getString()[i]){
                return false;
            }
        }
        return true;
    }  

    bool string_lessthan(String &s1, String &s2){
        if (s1.getString().size() < s2.getString().size()){
            return true;
        }
        return false;
    }    

    bool string_greaterthan(String &s1, String &s2){
        if (s1.getString().size() > s2.getString().size()){
            return true;
        }
        return false;
    }

    bool string_lessthan_equal(String &s1, String &s2){
        if (s1.getString().size() <= s2.getString().size()){
            return true;
        }
        return false;
    }

    bool string_greaterthan_equal(String &s1, String &s2){
        if (s1.getString().size() >= s2.getString().size()){
            return true;
        }
        return false;
    }



    std::vector<char> getString(){
        return a_string;
    }

private:
    std::vector <char> a_string;
}; 


}
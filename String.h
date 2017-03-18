#ifndef SHAKA_STRING_H
#define SHAKA_STRING_H
#include <vector>
#include <iostream>

namespace shaka{

class String{
public:
    //make new string with length "size" 
    String(int size){  
        a_string.resize(size);
    }

    //Create char vector with size "size" and initialize with character "b""
    String(int size, char b){

        for(int i = 0 ; i < size; i++){
            a_string.push_back(b); 
        }
    }

    //Makes a copy of a string
    String(String &c){
        for (int i = 0; i < (int)c.getString().size(); i++){
            a_string[i] = c.getString()[i];
            } 
    }

    String(String &c, int index1, int index2){

        for(int i=index1; i <= index2; i++){
            a_string[i] = c.getString()[i];
        }

    }

    //return length of a_string
     int string_length(){
        return static_cast<int>(a_string.size());
    }

    //takes the index, and returns the value of the index
    char string_ref(int index){

        for(int i = 0; i < (int)a_string.size(); i++){
            if (i == index){
                return a_string[index];
            }
        }
        return 'e';
    }
    void substring(String &c, int start, int end){
	for(int i=start; i < end; i++){
		a_string[i] = (c.getString())[i];
	}
    }


    void string_set(int index, char a){

        for(int i = 0; i < (int)a_string.size(); i++){
            if (i == index){
                a_string[index] = a;
            }
        }
    }
    void string_append(String &c){
	for(int i = 0; i!= (int)c.getString().size(); i++){
		a_string.push_back((c.getString())[i]);
	}
    }
    void string_copy(String &c){
	for(int i=0; i!= (int)c.getString().size(); i++){
		a_string[i] = (c.getString())[i];
	}
    }
    void string_copy(String &c, int start){
	for(int i=start; i!= (int)c.getString().size(); i++){
		a_string[i] = (c.getString())[i];
	}
    }
    void string_copy(String &c, int start, int end){
	for(int i=start; i!= end; i++){
		a_string[i] = (c.getString())[i];
	}
    }
    void string_fill(char fill){
	for(int i=0; i!=(int)a_string.size();i++){
		a_string[i] = fill;
	}
    }
    void string_fill(char fill, int start){
	for(int i=start; i!=(int)a_string.size();i++){
		a_string[i] = fill;
	}
    }
    void string_fill(char fill, int start, int end){
	for(int i=start; i!= end;i++){
		a_string[i] = fill;
	}
    }




/*//Need to make it case insensitive     
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
    }*/

     friend bool operator==(String& s1, String& s2){
        if(s1.a_string.size() != s2.a_string.size()){
            return false;
        }
        for(int i = 0; i < (int)s1.a_string.size(); i++){

            if(s1.a_string[i] != s2.a_string[i]){
                return false;
            }
        }
        return true;
    } 
	    
    friend bool operator!=(String& s1, String& s2){
        if(s1.getString().size() != s2.getString().size()){
            return true;
        }
        for(int i = 0; i < (int)s1.getString().size(); i++){

            if(s1.getString()[i] != s2.getString()[i]){
                return true;
            }
        }
        return false;
    }  

      //  return !(s1 == s2);
    
    friend bool operator<(String& s1, String& s2){
	if(s1.string_length() < s2.string_length())
		return true;
	return false;
        //return s1.a_string < s2.a_string;
    }
    friend bool operator>(String& s1, String& s2){
        if(s1.string_length() > s2.string_length())
		return true;
	return false;
    }
    friend bool operator<=(String& s1, String& s2){
        if(s1.string_length() <= s2.string_length())
		return true;
	return false;
    }
    friend bool operator>=(String& s1, String& s2){
        if(s1.string_length() >= s2.string_length())
		return true;
	return false;
    }

    std::vector<char>& getString(){
        return a_string;
    }

private:
    std::vector<char> a_string;
}; 


}
#endif // SHAKA_STRING_H

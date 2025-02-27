#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>  // For system() function
using namespace std;

class encryptDecrypt {
    private:
        string inputPath;
        vector<char> buffer;

    public:

        encryptDecrypt(string inputPath) {
            this->inputPath = inputPath;
            
             // Open the image file in binary mode
            ifstream image(inputPath, ios::binary);
            if (!image) {
            cerr << "Error opening input file!" << endl;
            }
            // Read file into a buffer (vector)
            vector<char> buf((istreambuf_iterator<char>(image)), istreambuf_iterator<char>());;
            this->buffer = buf;
            image.close();  // Close the input file
            //cout<<buffer.size()<<endl;
        }

        // cheking for prime 
        bool is_prime(int n){
            if(n<=1){
                return false;
            }
            for(int i=2;i<n;i++){
                if(n%i==0){
                    return false;
                }
            }
            return true;
        }


        // fubction for encrypt msg in buffer
        string encrypt(string msg ){
            vector<bool> msg1;

                // Convert each character of msg into  its binary representation(bits)
                for (char ch : msg) {
                    for (int i = 7; i >= 0; --i) {  // 8 bits per char
                        msg1.push_back((ch >> i) & 1);
                    }
                }

                // we made msg1 size as a key for securty
                cout<<"your key is "<<msg1.size()<<endl;

                // for(auto it :msg1){
                //     cout<<it<<" ";
                // }
               

            // logic for encrypt msg1 in buffer
                int j=0;
            for(int i=buffer.size()-10; i>0 && j<=msg1.size();i--){
            
                if(is_prime(i)){
                    if(msg1[j]==1){
                    buffer[i] = buffer[i] | msg1[j++];
                    }else{
                        buffer[i] = buffer[i] & msg1[j++];
                    }
                }
            }

          //  cout<<"Input path for the image to be restored is "<<inputPath<<endl;

          // we define a output path for encripted image.
            int index = inputPath.rfind('.'); // Finds the last occurrence of '.' 
            string outputPath = inputPath.substr(0 ,index)+"encypted" + inputPath.substr(index);  // Restored image

           // cout<<"Output path for the restored image is "<<outputPath<<endl;

                // class for retrive encrypted buffer in to img.
                    ofstream outputImage(outputPath, ios::binary);
                    if (!outputImage) {
                        cerr << "Error creating output file!" << endl;
                    }
                    // Write the buffer data to the new image file
                    outputImage.write(buffer.data(), buffer.size());
                    outputImage.close();  // Close the output file

                   // cout << "Image successfully restored as '" << outputPath << "'." << endl;
                    return outputPath;   
                }


                // retrive decripted msg from binary to string 
                string binaryToString(const vector<bool>& rmsg) {
                    string result;
                    for (size_t i = 0; i < rmsg.size(); i += 8) {
                        char ch = 0;
                        for (int j = 0; j < 8; ++j) {
                            ch = (ch << 1) | rmsg[i + j];  // Convert 8 bits to a character
                        }
                        result += ch;
                    }
                    return result;
                }

            // decrept msg from increpted buffer
        string decrypt(int key){
            vector<bool> rmsg;
            int j=0;
            for(int i=buffer.size()-10; i>0 && j<key; i--){
                if(is_prime(i)){
                rmsg.push_back(buffer[i] & 1);
                j++;
                }
            }

            // for(auto in : rmsg){
            //     cout<<in<<" ";
            // }

            return binaryToString(rmsg);
        }

};        
        


int main() {
    // File paths

    do {
        cout << "\nWelcome to Cryptography Application" << endl;
        cout << "Encrypt: Press 1" << endl;
        cout << "Decrypt: Press 2" << endl;
        cout << "Exit: Press 0" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        
        

        if (choice == 1) {
            string inputPath;  // Original image
            cout << "Enter the path of the image to be Encrypted: ";
            cin >> inputPath;

            encryptDecrypt obj(inputPath);
            string m;
            cout << "Enter message to encrypt: ";
            cin.ignore();  
            getline(cin, m);  // Read the full message (handles spaces)

            string output = obj.encrypt(m);
            cout << "Encrypted image: " << output << endl;
        }
        else if (choice == 2) {
            string inputPath;  // Original image
            cout << "Enter the path of the image to be Decrypt: ";
            cin >> inputPath;

            encryptDecrypt obj(inputPath);
            int key;
            cout << "Enter key : ";
            
            cin>>key;

            string decryptedMsg = obj.decrypt(key);
            cout << "Decrypted Message: " << decryptedMsg << endl;
        }
        else if (choice == 0) {
            cout << "Exiting Cryptography Application...\n";
            break;
        }
        else {
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (true);


    return 0;
}

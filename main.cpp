#include<iostream> //mengambil library Input Output Stream
#include<fstream> //menggambil library File Stream
#include<windows.h> //mengambil library dari OS windows
#include<mmsystem.h> //mengambil library dari windows.h yaitu Multi Media System Header
#include<algorithm>
#pragma comment(lib, "winmm.lib");
//lagu bisa diputar hanya setelah link dengan 'winmm' di linker

using namespace std;

void acak_soal(char soal[][12], int i); //mengacak soalaru
void tampil_soal(char soal[][12], int i); //menampilkan soal hasil acakan
string input_player(); //menerima input player.
bool check(string jawab, string jawaban); //membandingkan variabel jawab dan jawaban
void sound_start(); //prosedur untuk efek suara start
void sound_over(); //prosedur untuk efek suara game over
void read_high(); //membaca file highscore.txt dan menginput nya ke dalam struct High
void write_high(); //menulis hasil sorting ke dalam highscore.txt
void sort_highscore(); //mengsorting array player[1] sampai player[3]

struct High
{
    string name;
    int score;
} player[3]; //untuk menyimpan sementara nilai dan nama pemain dalam highscore.

int main()
{
    system("color f1");
    read_high(); //membaca highscore yang ada sebelum permainan dimulai
    PlaySound(LPCSTR("01"), NULL, SND_ASYNC); //memainkan lagu background
    char soal[5][12] = {"borobudur",
                        "batik",
                        "pontianak",
                        "komputer",
                        "processor"}; //array dimensi 2 untuk menyimpan soal. 5 soal, dan maksimal 12 karakter per soal

    int point = 0; //score
    int hp = 3; //nyawa
    char pilihan; //pilihan permainan
    cout<<"                           selamat datang di tebak kata (v 1.4)     "<<endl<<endl<<endl<<endl;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<endl<<endl<<endl<<endl;
    while(true) //looping untuk jaga" input yang tidak cocok dengan case yang ada.
    {
        cout<<"silahkan pilih salah satu option di bawah ini (1, 2, 3)"<<endl<<endl<<endl<<endl<<endl;
        cout<<"1. Start"<<endl<<endl<<"2. about"<<endl<<endl<<"3. highscore"<<endl<<endl<<"4. exit"<<endl;
        cin>>pilihan;
        switch(pilihan)
        {

            case '1':
                sound_start(); //memainkan efek suara start
                for(int i=0; i<5; i++)
                {
                    cout<<"HP : "<<hp<<"\t\t\t\t\t\t\t\t"<<"scores : "<<point<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
                    string jawaban = soal[i]; //menyimpan jawaban, yaitu soal itu sendiri, SEBELUM DIACAK
                    string jawab;
                    bool benar;
                    acak_soal(soal, i);
                    tampil_soal(soal, i);
                    jawab = input_player(); //menerima input playeer sekaligus memasukkanya kedalam variabel jawab
                    benar = check(jawab, jawaban); //menjalakan fungsi check() sekaligus memasukkan nilai kembalian fungsi check() ke dalam var benar
                    if(benar == true){
                        _beep(900, 100); //beep untuk efek suara, param1 = frekuensi, param2 = lama bunyi dalam milisecond
                        _beep(1200, 200);
                        point+=10; //point tambah 10, sama aja dengan point = point+10;
                    }else{
                        _beep(700, 100);
                        _beep(500, 200);
                        hp -=1; //mengurangi nyawa
                    }
                    if(hp==0){ //kondisi game over
                        if(point>player[2].score){ //mengecek apakah nilai kita masuk ke dalam highscore
                            player[2].score = point; //mengubah score posisi ke3 menjadi score kita
                            cout<<"input your name"<<endl;
                            cin>>player[2].name; //masukkan nama
                            sort_highscore(); //sorting
                            write_high(); // menulis hasil sorting ke dalam highscore.txt
                            break;
                        }
                        cout<<endl<<"game over"<<endl;
                        break;
                    }
                }
                cout<<"HP : "<<hp<<"\t\t\t\t\t\t\t\t"<<"scores : "<<point<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
                if(point>player[2].score && hp!=0){ //mengecek apakah nilai kita masuk ke dalam highscore
                        player[2].score = point; //mengganti posisi highscore k3 menjadi score kita
                        cout<<"input your name"<<endl;
                        cin>>player[2].name; //mengganti nama posisi highscore k3 menjadi nama inputan kita
                        sort_highscore(); //mengurutkan highscore setelah nama dan score kita dimasukkan
                        write_high(); //menuliskan hasil sorting ke dalam highscore.txt
                        break;
                        }
                while(true) //looping untuk men-jaga" input sembarang dari user bekerja sama dengan continue;
                {
                    cout<<"apakah anda ingin bermain lagi?(y or n)"<<endl; //looping game
                    char lagi;
                    cin>>lagi;
                    switch(toupper(lagi)) //mengubah segala input kita ke dalam upper case
                    {
                        case 'Y':
                            system("cls");
                            sound_start();
                            main(); //kembali mengeksekusi fungsi utama
                            break;
                        case 'N':
                            cout<<"Bye bye"<<endl;
                            sound_over();
                            exit(0); //keluar dari program
                            break;
                        default:
                            cout<<"pilihan salah, masukkan y atau n"<<endl;
                            continue; //kembali ke while(true)
                    }
                }
            break;
            case '2':
                cout<<endl<<"Nama Kelompok: "<<endl<<endl<<"Andy Herman (132 101 210)"<<endl<<endl<<"Benisius Rendi (132 101 245)"<<endl<<endl<<"Fajar AgusRiansyah (132 101 205)"<<endl<<endl<<"Iqbal Febrianto (132 101 227)"<<endl<<endl<<"Rury Permata Ayu N.F (132 101 235)"<<endl<<endl;
                break;

            case '3':
                cout<<"highscore:"<<"\n\n";
                for(int i=0; i<3; i++){
                    cout<<endl<<player[i].name<<"\t"<<player[i].score<<"\n\n";
                }
                break;

            case '4':
                cout<<"Bye bye"<<endl;
                sound_over();
                exit(0); //keluar dari program
                break;
            default: //bila pemain memasukkan input asal, selain case.
                _beep(200, 200);
                cout<<"tolong masukkan 1 - 3"<<endl;
                continue; //kembali ke while(true)
        }
    }
    return 0;
}


void acak_soal(char soal[][12], int i)
{
    int maks;
    int j;
    char check;
    for(j=0; j<12; j++) //looping untuk mendapatkan jumlah huruf dalam soal
    {
        check = soal[i][j];
        if(check == NULL) //mengecek eof dari array soal
        {
        maks=j; //memasukkan jumlah huruf ke dalam variabel maks
        break;
        }else{
        continue; //jika belum mendapatkan eof atau nilai null atau batas soal, akan terus ngeloop
        }
    }
    random_shuffle(&soal[i][0], &soal[i][maks]); //mengacak soal dengan menggunakan posisi awal dan posisi akhir yang baru saja kita dapat dari looping
}

void tampil_soal(char soal[][12], int i)
{
    int k;
    char j;
    for(k=0; k<12; k++)
    {
        j = soal[i][k];
        if(j ==NULL){ //jika mencapai eof(end of file) atau null, maka akan keluar dari looping
            break;
        }else{
            cout<<j<<"  |   ";
        }
    }
    cout<<endl<<endl<<endl<<endl<<endl<<endl;
}

string input_player()
{
    string jawab;
    cout<<endl<<endl<<endl<<endl<<"masukkan jawaban anda"<<endl;
    cin>>jawab;
    return jawab; //mengembalikan nilai masukkan kita
}

bool check(string jawab,string jawaban) //mengecek jawaban user
{
    if(jawab != jawaban){
        return false;
    }else{
        return true;
    }
}

void sound_start(){ //menghasilkan 4 nada secara beruurutan dengan frekuensi dan waktu yang berbeda
    _beep(400, 100);
    _beep(600, 100);
    _beep(800, 200);
    _beep(1000, 300);
}

void sound_over(){ //menghasilkan 4 nada secara beruurutan dengan frekuensi dan waktu yang berbeda
    _beep(1200, 200);
    _beep(1000, 100);
    _beep(800, 100);
    _beep(600, 200);
    _beep(400, 300);

}
void read_high(){
	ifstream myfile; //membuat objek ifstream( input file stream)
	myfile.open("highscore.txt"); //membuka file highscore.txt
	while(myfile){ //looping untuk memasukkan data dalam highscore.txt ke dalam array struct player
		for(int i=0; i<3; i++){
			myfile>>player[i].name;
			myfile>>player[i].score;
		}
		myfile.close(); //tutup highscore.txt
	}
}
void write_high(){
	ofstream myfile; //membuat objek ofstream(output file stream)
	myfile.open("highscore.txt"); //membuka file highscore.txt
	while(myfile){ //looping untuk memasukkan data  ke dalam highscore.txt
		for(int i=0; i<3; i++){
			myfile<<player[i].name;
			myfile<<"\n";
			myfile<<player[i].score;
			myfile<<"\n";
		}
		myfile.close(); //tutup highscore.txt
	}
}
void sort_highscore(){ //insertion sort untuk highscore
	int i, j, temp;
	string temp2;
	for(i=1; i<3; i++){
		temp = player[i].score;
		temp2 = player[i].name;
		j = i-1;
		while(player[j].score < temp && j>=0){
			player[j+1].score = player[j].score;
			player[j+1].name = player[j].name;
			j--;
		}
		player[j+1].score = temp;
		player[j+1].name = temp2;
	}
}

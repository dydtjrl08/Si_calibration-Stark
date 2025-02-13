

class Student{
	char name[10] = "yongseok";
	int id;
public:
	Student(const char *name,const int id = 0){
		this -> name = name;
		this -> id = id;
	}	
	void presentation(){
		cout << this->name << " " << this->id << endl;
		}
};

void te(){
	Student *yongseok = new Student("gwon",3);
	yongseok->presentation();
}

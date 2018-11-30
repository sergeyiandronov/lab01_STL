#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
void finit() {
	std::ofstream fout;
	fout.open("db.txt");
	fout<<"добрый сок 0.07\nдобрый вечер 0.1\n добрый утро 0.01\nдобрый человек 0.02\nспокойной ночи 0.21\n	спокойного сна 0.11\n";
	fout.close();
}
struct Entity
{
	std::string Query;
	float Frequency;
};

using Dict = std::multimap<std::string, Entity>;
std::vector<Entity> suggest(const Dict & dict, const std::string& currentWord) {
	std::vector<Entity> result;
	for (auto it = (dict.equal_range(currentWord)).first; it != (dict.equal_range(currentWord)).second; it++) {
		result.push_back(it->second);
	}
	std::sort(result.begin(), result.end(), [](Entity a, Entity b) {
		return (a.Frequency > b.Frequency);
	});
	return result;
};
std::multimap<std::string, Entity> load(const std::string& filename) {
	std::multimap<std::string, Entity> result;
	std::ifstream fin;
	std::string key;
	std::string query;
	float frequency;
	fin.open("db.txt");
	while (fin >> key) {
		if (!(fin >> query)) {
			return result;
		}
		if (!(fin >> frequency)) {
			return result;
		}
		result.insert({ key,{query,frequency} });
	}
	fin.close();
	return result;
};
struct Student
{
	std::string Name;
	std::string GroupId;
	std::map<std::string, unsigned> Ratings;
	Student(std::string Name, std::map<std::string, unsigned> Ratings) {
		this->Name = Name;
		this->Ratings = Ratings;
	}
	void print_student_rate() {
		
		for (auto it = Ratings.begin(); it != Ratings.end(); it++) {
			std::cout << "\n    \t" << it->first;
			std::cout << "\t" << it->second;
		}
	}
	float adv_rate() {
		float sum = 0;
		for (auto it = Ratings.begin(); it != Ratings.end(); it++) {
			sum += it->second;
		}
		return sum / Ratings.size();
	}
	bool neud(){
		bool result = false;
	    for (auto it = Ratings.begin(); it != Ratings.end(); it++) {
			if (it->second <= 2) {
				result = true;
				return result;

			}
	    }
		return result;
	}
	bool good() {
		bool result = true;
		for (auto it = Ratings.begin(); it != Ratings.end(); it++) {
			if (it->second < 5) {
				result = false;
				return result;

			}
		}
		return result;
	}
	bool good_at_math() {
		if (this->Ratings["Math"] == 5) {
			return true;
		}
		return false;
	}

};
void print_student(Student stud) {

	std::cout << "\n"<<stud.Name<<"\t average rating:"<<stud.adv_rate();
	stud.print_student_rate();
}
void good_politology(Student& pol) {
	pol.Ratings["Politology"] = 5;
	
}
void print_entity(Entity& ent) {
	std::cout << "\n {" << ent.Query <<","<<ent.Frequency<<"} \t";
}

int main() {
	std::cout << "Zadanie 1\n";
	Student s1("Alefirov", { {"Politology",5},{"OFP",5},{"Math",4} }),
		s2("Andronov", { { "Politology",5 },{ "OFP",5 },{ "Math",5 } }),
		s3("Borisov", { { "Politology",4 },{ "OFP",3 },{ "Math",3} }),
            s4("Bondarenko", { { "Politology",3 },{ "OFP",4 },{ "Math",4 } });
	std::vector<Student> students{s2,s4,s3,s1};
	
	std::sort(students.begin(), students.end(), [](Student a,Student b) {
		return (a.Name.compare(b.Name)<0);
	});
	for_each(students.begin(), students.end(), print_student);
	std::cout << "\n----------\n";
	std::sort(students.begin(), students.end(), [](Student a, Student b) {
		
		return (a.adv_rate()>b.adv_rate());
	});
	for_each(students.begin(), students.end(), print_student);
	std::cout << "\n-----------\n";
	unsigned int count_of_neud=std::count_if(students.begin(), students.end(), [](Student a) {

		return a.neud();
	});
	std::cout << count_of_neud;
	std::cout << "\n----------\n";
	unsigned int count_of_good = std::count_if(students.begin(), students.end(), [](Student a) {

		return a.good();
	});
	std::cout << count_of_good;
	std::vector<Student> exlents = {s3};
	std::cout << "\n-------\n";
    std::copy_if(students.begin(), students.end(),exlents.begin(), [](Student a) {

		return a.good_at_math();
	});
	for_each(exlents.begin(), exlents.end(), print_student);
	std::cout << "\n--------\n";
	
	std::transform(students.begin(), students.end(), students.begin(), [](Student a) {
		good_politology(a);
		return a;
	});
	for_each(students.begin(), students.end(), print_student);
	std::cout << "\n";
	std::cout << "Zadanie 2\n";
	setlocale(LC_ALL,"Russian");
	finit();
	auto dict = load("db.txt");
	auto result = suggest(dict, "добрый");
	if (!(result.empty())) {
		for_each(result.begin(), result.end(), print_entity);
	}
	system("pause");
}
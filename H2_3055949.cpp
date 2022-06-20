/*
Task: H2
Family Name: Mannan
Given Name: Nasif
Matriculation number: 3055949
Uni-Email: nasif.mannan@stud.uni-due.de
Course of Studies: ISE CSE
*/
#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include<cmath>

using namespace std;

struct obstacle{
	string name;
	double x;
	double y;
	double dist;
	struct obstacle *next;
};

double eucledianDistance(obstacle p1, obstacle p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

obstacle* closestPoint(obstacle* head, obstacle pt){
	obstacle* temp = head, *closestPoint = NULL;
	if(temp == NULL || temp->next == NULL)
		return closestPoint;
	double closestDist = -1, tempDist;
	while(temp!=NULL){
		if(temp->name != pt.name){
			tempDist = eucledianDistance(*temp, pt);
			if(closestDist < 0){
				closestDist = tempDist;
				closestPoint = temp;
			}
			else if(closestDist > tempDist){
				closestDist = tempDist;
				closestPoint = temp;
			}
		}
		temp = temp->next;
	}
	return closestPoint;
}

obstacle* sortedInsert(obstacle* head, obstacle *pt){
	if(head == NULL){
		return pt;
	}
	if(head->dist > pt->dist){
		pt->next = head;
		return pt;
	}
	obstacle *temp = head, *prev = NULL;
	while(temp!=NULL){
		if(temp->dist > pt->dist){
			prev->next = pt;
			pt->next = temp;
			return head;
		}
		prev = temp;
		temp = temp->next;
	}
	prev->next = pt;
	return head;
}

void printObstacle(obstacle* head){
	obstacle* temp = head;
	cout<<fixed<<setprecision(2);
	while(temp!=NULL){
		cout<<"obstacle "<<right<<setw(2)<<temp->name<<": ("<<right<<setw(6)<<temp->x<<", "<<right<<setw(6)<<temp->y<<"), distance:"
			<<right<<setw(6)<<temp->dist<<"m, nearest to this: "<<(closestPoint(head, *temp))->name<<endl;
		temp = temp->next;
	}
}

void clean(obstacle *head){
	cout<<"delete:";
	obstacle* temp = head, *prev = NULL;
    if(temp == NULL)
    	return;
    while(temp!=NULL){
    	prev = temp;
		temp = temp->next;
		cout<<" "<<prev->name;
		delete prev;
	}
	cout<<endl;
}

int main(){
	obstacle* list = NULL;
	obstacle origin;
	origin.x = 0;
	origin.y = 0;
	string name;
	double x, y;
	while(1){
		cout<<"string describing obstacle (\"end\" for end of input): ";
		cin>>name;
		if(name == "end")
			break;
		cout<<"x and y coordinate: ";
		cin>>x>>y;
		obstacle* val = new obstacle;
		val->name = name;
		val->x = x;
		val->y = y;
		val->dist = eucledianDistance(*val, origin);
		val->next = NULL;
		list = sortedInsert(list, val);
	}
	printObstacle(list);
	clean(list);
	return 0;
}

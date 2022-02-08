#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <memory>
#include <vector>
#include <time.h>
#include <cstdlib>

using namespace std; 

struct Nonterminal {
	string name;
	vector <string> set;
	string out;
	bool notSemi;
};

vector <Nonterminal> grammer;
vector <Nonterminal> firstSet;

void getNon () { // 讀近來
	char s;
	char eN = '\0';
	int i = 0, j = 0;
	string stay1 = "\0";
	Nonterminal stay2;
	stay2.notSemi = true;
	
	s = cin.peek();
	bool hasName= false;
	
	while ( s != '\n' && s != EOF ) {
		cin >> s ;
		
		if ( s == 'E' ) {
			eN = cin.peek();
			
			if ( eN == 'N' ) { // END
				while( s != '\n' && s != EOF ) {
					cin >> s ;
					s = cin.peek();
				} // while
			} // if
		} // if
		
		if ( s >= 'A' && s <= 'Z' ) {			
			if ( !hasName ) {
				hasName= true;
				stay1 = stay1 + s;
				stay2.name = stay1;
				stay1 = "\0";
			} // if
			else {
				stay1 = stay1 + s;
			} // else
		} // if
		else if ( s >= 'a' && s <= 'z' ) {
			stay1 = stay1 + s;
		} // else if
		else if ( s == '$' ) {
			stay1 = stay1 + s;
			stay2.out = "\0";
			stay2.set.push_back( stay1 );
			stay1 = "\0";
		} // else
		else if ( s == ';' ) {
			stay1 = stay1 + s;
			stay2.out = "\0";
			stay2.set.push_back( stay1 );
			stay1 = "\0";
		} // else
		else if ( s == '\|' ) { // 處理 | 
			if ( stay1 != "\0" ) {
				stay2.out = "\0";
				stay2.set.push_back( stay1 );
				stay1 = "\0";
			} // if
		} // else
		
		s = cin.peek();
	} // while
	
	if ( stay1 != "\0" ) {
		stay2.out = "\0";
		stay2.set.push_back( stay1 );
		stay1 = "\0";
	} // if
	
	if ( stay2.name != "\0" ) {
		grammer.push_back( stay2 );
	} // if
} // getNon

bool getFSet ( int i , int j ) { // 切出來 
	
	int strLen = 0, com = 0 , k = 0;
	int setLen = grammer[i].set.size(), l  = 0;
	char a = '\0', b = '\0';
	int hasSemi = -1, DoSet = 0;
	string stay1 = "\0";
	string stay2 = "\0";
	
	stay1 = grammer[i].set[j];
	strLen = stay1.size();
	
	while ( com < strLen ) { // 一個set一個set找 ex ABb aA 
		a = stay1[com];
		k = 0;
		if ( a >= 'a' && a <= 'z' ) {
			com = strLen;
			grammer[i].out = grammer[i].out + a;
		} // if
		else if ( a >= 'A' && a <= 'z' ) { // function 
			while ( k < grammer.size() ) { // 找到對應得set 
				stay2 = a;
				if ( grammer[k].name == stay2 ) {
					getFSet ( k , 0 ); // 往下一圈飽 
					if ( com == strLen - 1 ) { // function最尾位
						stay2 = grammer[k].out;
						if ( hasSemi != -1 ) { // 前面的有; ;不能進來 
							grammer[i].out = grammer[i].out + grammer[k].out;
						}// if
						else if ( com == 0 ) { //  set只有一個function
							grammer[i].out = grammer[i].out + grammer[k].out;
						} // else if
					} // if
					else {
						stay2 = grammer[k].out;
						for ( l = 0 ; l < stay2.size() ; l++ ) { // 檢查set的out有沒有; 
							b = stay2[l];
							
							if ( DoSet > 0 && hasSemi == -1 ) { //不是第一個且前面的沒; 
								l = stay2.size();
							}  // if
							else {
								if ( b != ';' ) { // 不是; 
									grammer[i].out = grammer[i].out + b; 
								} // if
								else {
									hasSemi = l;
								} // else							
							} // else
						} // for
					} // else
					
					k = grammer.size();
					DoSet++;
				} // if	
				
				stay2 = "\0";
				k++;
			} // while
		} // else if
		else if ( a == ';' ) {
			com = strLen;
			grammer[i].out = grammer[i].out + a;
		} // else if
		else if ( a == '$' ) {
			com = strLen;
			if ( hasSemi != -1 ) {
				grammer[i].out = grammer[i].out + a;
			} // if
			
		} // else if
		
		com++;
	} // while
	
	if ( j + 1  < setLen ) {
		getFSet ( i , j + 1 );
	} // if
	else if ( i + 1 < grammer.size() ) {
		getFSet ( i + 1 , 0 );
	} // else if
	
	return true;
	
} // getFSet ()

void outSet() {
	char a = '\0';
	string stay1 = "\0";
	string stay2 = "\0";
	string change = "\0";
	int i = 0, j = 0, k = 0 ;
	int l = 0, m = 0, n = 0;
	int setLen = 0, strLen = 0, com = 0;
	int allBig = -1;
	bool hasSemi = false;
	bool hasLow = false;
	bool hasMon = false;
	bool same = false;
	vector <char> outF;
	
	for ( i = 0 ; i < grammer.size() ; i++ ) {
		stay1 =  grammer[i].out;
		strLen = grammer[i].out.size();
		for ( j = 0 ; j < strLen ; j++ ) {
			stay1 =  grammer[i].out[j];
			if ( stay1 == ";" ) {
				grammer[i].notSemi = false;
				j = strLen;
			} // if
		} // for
	} // for
	
	j = 0;
	for ( i = 0 ; i < grammer.size() ; i++ ) { // Nonterminal總數 
		setLen = grammer[i].set.size();
		while ( j < setLen ) { // Nonterminal的set的Token數量 
			stay1 =  grammer[i].set[j];
			strLen = stay1.size();
			a = stay1[0]; // 第一個 
			if ( a >= 'a' && a <= 'z' ) {
				// 屬於FS 沒特例 skip 
			} // if
			else if ( a >= 'A' && a <= 'Z' ) { // 開頭大寫  檢查有沒有小寫 
				k = 1;
				while ( k < strLen ) {
					a = stay1[k];
					if ( a >= 'a' && a <= 'z' ) {
						k = strLen;
					} // if
					else if ( a == '$' ) {
						hasMon = true;
					} // if	
					
					if ( k == strLen - 1 ) {
						allBig = j; // 跑到最後才會設 
					} // if 
					
					k++;
				} // while				
			} // else if
			else if ( a == ';' ) {
				hasSemi = true;
			} // else if
			else if ( a == '$' ) {
				hasMon = true;
			} // else if
			
			j++;
		} // while
		
		stay1 =  grammer[i].out;
		strLen = grammer[i].out.size();
		k = 0;
		
		while ( k < strLen ) {
			a = stay1[k];
			if ( a >= 'a' && a <= 'z' ) { 
				same = false;
				for ( l = 0 ; l < outF.size() ; l++ ) {
					// b = outF[l];
					if ( a == outF[l] ) { // 直接放  
						same = true;
					} // if
				} // while
				
				if ( !same ) {
					outF.push_back(a);
				} // if
			} // if
			else if ( a == ';' ) {
				if ( hasSemi ) { // 本身有; 
					outF.push_back(a);
					hasSemi = false;
					hasLow = true;
				} // if
				else if ( allBig != -1 ) { // 全大寫 
					stay1 =  grammer[i].set[allBig]; // 找到那一個 
					strLen = stay1.size();
					for ( l = 0 ; l < strLen - 1 ; l++ ) { // 按字串長度去找 
						stay2 = stay1[l];
						for ( m = 0 ; m < grammer.size() ; m++ ) {
							if ( stay2 == grammer[m].name ) {
								if ( grammer[m].notSemi == false ) { // 有; 
									allBig = -2 ;
									m = grammer.size();
									l = strLen;
								} // if
							} // if
						} // for
					} // for
					
					if ( allBig == -2 ) {
						outF.push_back(a);
						allBig = -1;
					} // if
					
					stay1 =  grammer[i].out;
					strLen = grammer[i].out.size();
				} // if
				 
			} // else if
			else if ( a == '$' ) {
				if ( hasMon ) {
					outF.push_back(a);
					hasMon = false;
				} // if
			} // else if
			
			k++;
		} // while
		
		for ( k = 0 ; k < outF.size() ; k++ ) {
			for ( l = 0 ; l < outF.size() ; l++ ) {
				if ( outF[k] < outF[l] ) {
					a = outF[k];
					outF[k] = outF[l];
					outF[l] = a;
				} // if
			} // for
		} // for
		
		k = 0;
		while ( k < outF.size() ) {
			change = change + outF[k];
			k++;
		} // while
		
		grammer[i].out = change;
		
		j = 0;
		change = "\0";
		outF.clear();
		hasSemi = false;
		hasMon = false;
		hasLow = false;
		allBig = -1;
	} // while
	
	for ( i = 0 ; i < grammer.size() ; i++ ) {
		for ( j = 0 ; j < grammer.size() ; j++ ) {
			if ( grammer[i].name < grammer[j].name ) {
				stay1 = grammer[i].name;
				grammer[i].name = grammer[j].name;
				grammer[j].name = stay1;
				stay1 = grammer[i].out;
				grammer[i].out = grammer[j].out;
				grammer[j].out = stay1;
			} // if
		} // for
	} // for
	
	
} // outSet()

int main() {
	int i = 0 , j = 0, k = 0;
	char a;
	a = cin.peek();
	
	while ( a != EOF ) {
		getNon ();
		a = cin.peek();
		if ( a == '\n' ) {
			scanf( "%c", & a );
			a = cin.peek();
		} // if
		
	} // while
	
	getFSet ( i , j );
	/*
	while ( i < grammer.size() ) {
		cout << grammer[i].name << " " << grammer[i].out << "\n";
		i++;
	} // while
	*/
	outSet();
	
	while ( i < grammer.size() ) {
		cout << grammer[i].name << " " << grammer[i].out << "\n";
		i++;
	} // while
	
	cout << "END_OF_FIRST\n";
	
	return 0;
} // main 

#include "YoudaoDict.h"
int Dict::count = 0;

 YoudaoDict::YoudaoDict()
 {
	dict = NULL;
 }
 
 YoudaoDict::~YoudaoDict()
 {
	 if (dict)
		 DeleteSite();
 }

void YoudaoDict::MainMenu()
{
	bool a = true;
	while (a)
	{
		system("cls");
		cout << "1����ѯ����" << endl;
		cout << "2��׷�ӵ���" << endl;
		cout << "3��ɾ������" << endl;
		cout << "4���˳�ϵͳ" << endl;
		char b;
		b = getch();
		switch (b)
		{
		case '1':ShowWord(); break;
		case '2':AppWord(); break;
		case '3':DeleteWord(); break;
		case '4':a = false;break;
		default:
			cout << "��Чѡ�����������룡" << endl;
			break;
		}
		if (dict)
			DeleteSite();
		system("pause");
	}
}

void YoudaoDict::ShowWord()
{
	bool a = true;
	Dict*p = NULL;
	cout << "��������Ҫ��ѯ�ĵ��ʣ�";
	cin >> Word3;
	Tem = Word3[0];
	ReadWord();
	p = Judge();
	if (p)
		cout << *p << endl;
	else
		cout << "û�иõ���" << endl;

}

void YoudaoDict::AppWord()
{
	bool a = true;
	Dict*p = NULL;
	cout << "��������Ҫ��ӵĵ��ʣ�";
	cin >> Word3;
	cout << endl;
	Tem = Word3[0];
	ReadWord();
	p = Judge();
	if (!p)
	{
		fdict.open(fname, ios::app);
		if (!fdict)
		{
			cout << "�޷���ӣ�" << endl;
		}
		fdict << endl << Word3 << endl;
		cout << "������ע�ͣ�";
		cin >> Word3;
		fdict << Word3;
		fdict.close();
		cout << "��ӳɹ���" << endl;
	}
	else
	{
		cout << "���иõ��ʣ��Ƿ��޸ĸõ�����Ϣ  Y/N" << endl;
		while (true)
		{
			char i = getch();
			if (i == 'Y' || i == 'y')
			{
				cout << "ԭ����ע�ͣ�" << endl;
				cout << *p;
				cout << "������Ҫ�޸ĵ�ע�ͣ�";
				cin >> p->Word2;
				Save();
				cout << "��ӳɹ���" << endl;
				break;
			}
			else if (i == 'N' || i == 'n')
				break;
		}
	}
}

void YoudaoDict::DeleteWord()
{
	bool a = true;
	Dict*p = NULL;
	cout << "��������Ҫɾ���ĵ��ʣ�";
	cin >> Word3;
	cout << endl;
	Tem = Word3[0];
	ReadWord();
	p = Judge();
	if (p)
	{
		Dict *p1, *p2, *p3;
		for (p1 = p2 = dict; p2 != NULL; p2 = p3)
		{
			p3 = p2->p;
			if (strcmp(p2->Word1, Word3) == 0)
			{
				if (p2 == dict)
				{
					delete dict;
					dict = p3;
					break;
				}
				delete p2;
				p1->p = p3;
				break;
			}
			p1 = p2;
		}
		Save();
		cout << "ɾ���ɹ���" << endl;
	}
	else
		cout << "û�иõ���" << endl;
}

bool YoudaoDict::Fread(char t)
{
	bool a = true;
	switch (t)
	{
	case 'a':fname = "word list\\a.dat"; break;
	case 'b':fname = "word list\\b.dat"; break;
	case 'c':fname = "word list\\c.dat"; break;
	case 'd':fname = "word list\\d.dat"; break;
	case 'e':fname = "word list\\e.dat"; break;
	case 'f':fname = "word list\\f.dat"; break;
	case 'g':fname = "word list\\g.dat"; break;
	case 'h':fname = "word list\\h.dat"; break;
	case 'i':fname = "word list\\i.dat"; break;
	case 'j':fname = "word list\\j.dat"; break;
	case 'k':fname = "word list\\k.dat"; break;
	case 'l':fname = "word list\\l.dat"; break;
	case 'm':fname = "word list\\m.dat"; break;
	case 'n':fname = "word list\\n.dat"; break;
	case 'o':fname = "word list\\o.dat"; break;
	case 'p':fname = "word list\\p.dat"; break;
	case 'q':fname = "word list\\q.dat"; break;
	case 'r':fname = "word list\\r.dat"; break;
	case 's':fname = "word list\\s.dat"; break;
	case 't':fname = "word list\\t.dat"; break;
	case 'u':fname = "word list\\u.dat"; break;
	case 'v':fname = "word list\\v.dat"; break;
	case 'w':fname = "word list\\w.dat"; break;
	case 'x':fname = "word list\\x.dat"; break;
	case 'y':fname = "word list\\y.dat"; break;
	case 'z':fname = "word list\\z.dat"; break;
	default:a = false;
		break;
	}
	return a;
}

void YoudaoDict::ReadWord()
{
	if (Fread(Tem))
	{
		bool a = true;
		fdict.open(fname, ios::in);
		if (!fdict)
		{
			cout << "�޷�û������ļ�!" << endl;
			a = false;
		}
		if (fdict.eof())
		{
			cout <<"�ʿ���û�е��ʣ�" << endl;
			a = false;
		}
		if (a)
		{
			Dict *p1, *p2;
			int i = 0;
			for (p1 = dict = new Dict, p2 = NULL; true; p1 = p2)
			{
				fdict >> *p1;
				++i;
				if (fdict.eof())
				{
					if (i == 1)
					{
						p1->p = p2;
						break;
					}
					p2 = NULL;
					p1->p = p2;
					break;
				}
				p2 = new Dict;
				p1->p = p2;
			}
		}
		fdict.close();
	}
}

Dict* YoudaoDict::Judge()
{
	if (dict)
	{
		Dict *p1, *p2;
		for (p1 = dict; p1!=NULL; p1 = p2)
		{
			p2 = p1->p;
			if (strcmp(p1->Word1, Word3) == 0)
				return p1;
		}
	}
	return NULL;
}

void YoudaoDict::Save()
{
	fdict.open(fname, ios::out);
	Dict *p1,*p2;
	for (p1 = dict; p1; p1 = p2)
	{
		p2 = p1->p;
		if (p2 == NULL)
		{
			fdict << *p1;
			break;
		}
		fdict << *p1 << endl;
	}
	fdict.close();
}

void YoudaoDict::DeleteSite()
{
	Dict *p1, *p2;
	int i = 0;
	for (p1 = dict; p1; p1 = p2)
	{
		++i;
		p2 = p1->p;
		delete p1;
	}
	dict = NULL;
}
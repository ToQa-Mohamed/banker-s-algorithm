#include <iostream>
using namespace std;

int main()
{
	int p, r;
	int enter;
	int index = 0;
	int x = 0;
	cout << "enter the number of processes: " << endl;
	cin >> p;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "enter the number of resources: " << endl;
	cin >> r;
	cout << "------------------------------------------------------------------------------------------------" << endl;



	int* alloc = new int[p * r];
	int* max = new int[p * r];
	int* need = new int[p * r];
	int* available = new int[r];
	int* request = new int[r];
	int* finish = new int[p];
	int* seq = new int[p];

	cout << "enter the allocation matrix:";
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < r; j++) {
			cin >> *(alloc + i*r + j);
		}
	}
	cout << "------------------------------------------------------------------------------------------------" << endl;


	cout << "enter the max matrix:";
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < r; j++) {
			cin >> *(max + i*r + j);
		}
	}
	cout << "------------------------------------------------------------------------------------------------" << endl;


	cout << "enter the available resources vector:";
	for (int i = 0; i < r; i++)
	{
		cin >> available[i];
	}
	cout << "------------------------------------------------------------------------------------------------" << endl;



	cout << "if you want to know if the system is in a safe state enter 1, and if you want to know if a certain" << endl << "immediate request by one of the processes can be granted enter 2:" << endl;
	cin >> enter;
	cout << "------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < p; i++) {
		for (int j = 0; j < r; j++) {

			*(need + i*r + j) = *(max + i*r + j) - *(alloc + i*r + j);

		}
	}

	cout << "need matrix:" << endl;
	for (int i = -1; i < p; i++)
	{
		for (int j = -1; j < r; j++) {
			if (i == -1 && j == -1)
			{
				cout << "    ";
			}
			else if (i == -1 && j > -1)
			{
				cout << "R" << j << " ";
			}
			else if (i != -1 && j == -1)
			{
				cout << "P" << i << "  ";
			}
			else cout << *(need + i*r + j) << "  ";
		}
		cout << endl;

	}
	cout << "------------------------------------------------------------------------------------------------" << endl;




	if (enter == 1) {


		for (int k = 0; k < p; k++) {
			finish[k] = 0;
		}


		for (int k = 0; k < p; k++) {
			for (int i = 0; i < p; i++) {
				if (finish[i] == 0) {

					int flag = 0;
					for (int j = 0; j < r; j++) {
						if (*(need + i*r + j) > available[j]) {
							flag = 1;
							break;
						}
					}

					if (flag == 0) {
						seq[index++] = i;
						for (int x = 0; x < r; x++)
							available[x] += *(alloc + i*r + x);
						finish[i] = 1;
					}
				}
			}
		}

		int f_flag = 0;
		for (int i = 0;i < p;i++)
		{
			if (finish[i] == 0)
				f_flag = 1;
		}



		if (f_flag == 0)
		{
			cout << "yes,Safe state" << endl;
			cout << "<";
			for (int i = 0; i < p - 1; i++)
				cout << "P" << seq[i] << ",";
			cout << "P" << seq[p - 1] << ">" << endl;
		}
		if (f_flag == 1)
		{
			cout << "no" << endl;
		}
		cout << "------------------------------------------------------------------------------------------------" << endl;

	}


	if (enter == 2)
	{
		int req;
		int s_flag = 0;
		cout << "enter the process number(the first process is 0):" << endl;
		cin >> req;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		cout << "enter the request vector:" << endl;
		for (int i = 0; i < r; i++)
		{
			cin >> request[i];
		}
		cout << "------------------------------------------------------------------------------------------------" << endl;

		for (int i = 0; i < r; i++)
		{
			if (request[i] <= *(need + req*r + i))
			{
				if (request[i] <= available[i])
				{
					available[i] = available[i] - request[i];
					*(alloc + req*r + i) = *(alloc + req*r + i) + request[i];
					*(need + req*r + i) = *(need + req*r + i) - request[i];

				}
				else s_flag = 1;
			}
			else s_flag = 1;
		}


		if (s_flag == 0)
		{
			for (int k = 0; k < p; k++) {
				finish[k] = 0;
			}


			for (int k = 0; k < p; k++) {
				for (int i = 0; i < p; i++) {
					if (finish[i] == 0) {

						int flag = 0;
						for (int j = 0; j < r; j++) {
							if (*(need + i*r + j) > available[j]) {
								flag = 1;
								break;
							}
						}

						if (flag == 0) {
							seq[index++] = i;
							for (int x = 0; x < r; x++)
								available[x] += *(alloc + i*r + x);
							finish[i] = 1;
						}
					}
				}
			}

			int f_flag = 0;
			for (int i = 0;i < p;i++)
			{
				if (finish[i] == 0)
					f_flag = 1;
			}



			if (f_flag == 0)
			{
				cout << "Yes request can be granted with safe state , Safe state:" << endl;
				cout << "<P" << req << "req,";
				for (int i = 0; i < p - 1; i++)
					cout << "P" << seq[i] << ",";
				cout << "P" << seq[p - 1] << ">" << endl;
			}
			if (f_flag == 1)
			{
				cout << "no" << endl;
			}

		}
		else cout << "no" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

	}



	delete[] alloc;
	delete[] max;
	delete[] available;
	delete[] finish;
	delete[] seq;
	delete[] need;
	delete[] request;

	system("pause");
	return 0;
}


#include<iostream>
#include<math.h>
#include <iomanip>
using namespace std;
using std::setw;
class QuineMccluskey
{
	public:
		int binary[10];
		int num,numOfOne,noOfBits;bool used,isZero,isPrime;
		QuineMccluskey(int noOfBit)
		{
			used = false;
			isPrime = false;
			isZero = true;
			noOfBits = noOfBit;
			numOfOne = 0;
			for(int i = 0 ; i <noOfBits ; i++)
			{
				binary[i] = 0;
			}
		}
		void calcBinary()
		{
			int cn = num;
			for(int i = 0,j = noOfBits - 1; i < noOfBits ; i++,j--)
		    {
		        if(cn>=pow(2,j))
		        {
			        binary[i] = 1;
			        cn = cn - pow(2,j);
				}
				else
			   	{
			   		binary[i] = 0;
			   	}
			}
		    numberOfOnes();
		}
		void binaryDisplay()
		{
			for(int i = 0; i < noOfBits ; i++)
			{
				cout<<binary[i];
			}
			cout<<endl;
		}
		void numberOfOnes()
		{
			numOfOne = 0;
			for(int i = 0 ; i < noOfBits ; i++ )
			{
				if(binary[i]==1)
				{
					numOfOne++;
				}
			}
		}
		void printData()
		{
			cout<<"Number:"<<num<<"\t";
			cout<<"Is Zero:"<<isZero<<"\t";
			cout<<"Is Prime:"<<isPrime<<"\t";
			cout<<"Number of 1's:"<<numOfOne<<"\t";
			cout<<"Binary:";
			binaryDisplay();
		}
};
class QuineMccluskeyOutput
{
	public:
		int binary[10],noOfDash,dashpos[2],numused[4],noOfOne,noOfBits;bool used,isEmpty;
		QuineMccluskeyOutput( int noOfBit)
		{
			used = false;
			isEmpty = true;
			noOfBits = noOfBit;
			for(int i = 0; i < noOfBits ; i++)
			{
				//Consider -10 as nothing
				binary[i] = 0;
				if(i<2)
				{
					dashpos[i] = -10;
				}

			}
			for(int i = 0 ; i < 4 ; i++)
			{
				numused[i] = -10;
			}
			noOfOne = 0;
		}
		void calcNoOfOne()
		{
			for(int i = 0; i < noOfBits ; i++)
			{
				if(binary[i]==1)
				{
					noOfOne++;
				}
			}
		}
		void printBinary()
		{
			cout<<"Binary:";
			for(int z = 0; z < noOfBits; z++)
			{
				if(binary[z] >= 0)
					cout<<binary[z];
				else
					cout<<"-";
			}
			cout<<"\t";
		}
		void printData()
		{
			printBinary();
			cout<<"NoOfDash:"<<noOfDash<<"\tused:"<<used<<"\tNumber of 1's:"<<noOfOne;
			cout<<"\tDash pos:";
			for(int y = 0; y < 2; y++)
			{
				if( dashpos[y]!= -10 )
				{
					cout<<dashpos[y]<<"  ";
				}

			}
			cout<<"\tNumber Used:";
			for(int y = 0; y < 4; y++)
			{
				if( numused[y]!= -10 )
				{
					cout<<numused[y]<<"\t";
				}
			}
			cout<<endl;
		}
};
void calculateOutput(int noOfBits,int noOfOutput);
/*Q(n) Q(n+1) J K*/
int JKExitationTable[4][4]= {
								{0,0,0,-1},
								{0,1,1,-1},
								{1,0,-1,1},
								{1,1,-1,0}
							};
/*J K Q(n) Q(n+1)*/
int JKExtendedTable[8][4] = {
								{0,0,0,0},
								{0,0,1,1},
								{0,1,0,0},
								{0,1,1,0},
								{1,0,0,1},
								{1,0,1,1},
								{1,1,0,1},
								{1,1,1,0}
							};
/*Q(n) Q(n+1) S R*/
int SRExitationTable[4][4]= {
								{0,0,0,-1},
								{0,1,1,0},
								{1,0,0,1},
								{1,1,-1,0}
							};
/*S R Q(n) Q(n+1)*/
int SRExtendedTable[8][4] = {
								{0,0,0,0},
								{0,0,1,1},
								{0,1,0,0},
								{0,1,1,0},
								{1,0,0,1},
								{1,0,1,1},
								{1,1,0,-1},
								{1,1,1,-1}
							};
/*Q(n) Q(n+1) T*/
int TExitationTable[4][3] = {
								{0,0,0},
								{0,1,1},
								{1,0,1},
								{1,1,0}
							};
/*T Q(n) Q(n+1)*/
int TExtendedTable[4][3]  = {
								{0,0,0},
								{0,1,1},
								{1,0,1},
								{1,1,0}
							};
/*Q(n) Q(n+1) D*/
int DExitationTable[4][3] = {
								{0,0,0},
								{0,1,1},
								{1,0,0},
								{1,1,1}
							};
/*D Q(n) Q(n+1)*/
int DExtendedTable[4][3] =  {
								{0,0,0},
								{0,1,0},
								{1,0,1},
								{1,1,1}
							};
int wanted,available,col,row;
int finalTable[8][6];
int main(int argc, char** argv) {

	cout<<"1.JK FlipFlop\n2.SR FlipFlop\n3.T FlipFlop\n4.D FlipFlop\n Which of the above FlipFlop do you want to generate:";
	cin>>wanted;
	cout<<"1.JK FlipFlop\n2.SR FlipFlop\n3.T FlipFlop\n4.D FlipFlop\n Which of the above FlipFlop do you have:";
	cin>>available;
	if(wanted == available)
	{
		cout<<"You have the required FlipFlop no need to generate!!!";

	}
	if((wanted < 1 && wanted > 4) || (available < 1 && available > 4))
	{
		cout<<"You have chosen invalid request please try again!!!";

	}
	if(wanted>0 && wanted < 3)
	{
		row = 8;
	}
	else
	{
		row = 4;
	}
	if(wanted + available == 7)
	{
		col = 4;
	}
	else if(wanted + available == 3)
	{
		col = 6;
	}
	else
	{
		col = 5;
	}
	cout<<"----------------------------Following is Truth Table Required for given conversion----------------------------\n";
	if(wanted <3)
	{
		for(int i = 0; i < row ; i++)
		{
			for(int j = 0; j < 4 ; j++)
			{
				if(wanted == 1)
				{
					finalTable[i][j] = JKExtendedTable[i][j];
				}
				else
				{
					finalTable[i][j] = SRExtendedTable[i][j];
				}

			}
		}
	}
	else
	{
		for(int i = 0; i < row ; i++)
		{
			for(int j = 0; j < 3 ; j++)
			{
				if(wanted == 3)
				{
					finalTable[i][j] = TExtendedTable[i][j];
				}
				else
				{
					finalTable[i][j] = DExtendedTable[i][j];
				}
			}
		}
	}
	if(wanted + available == 3)/*Double to Double*/
	{
		int t1,t2;
		for(int i = 0; i < row; i++)
		{
			t1 = finalTable[i][2]; t2 = finalTable[i][3];
			for(int j = 0; j < 4 ; j++)
			{
				if(available == 1)
				{
					if(t1>=0 && t2>=0)
					{
						if(JKExitationTable[j][0]==t1 && JKExitationTable[j][1]==t2)
						{
							finalTable[i][4] = JKExitationTable[j][2];finalTable[i][5] = JKExitationTable[j][3];
						}
					}
					else
					{
						finalTable[i][4] = -1;finalTable[i][5] = -1;
					}
				}
				else
				{
					if(t1>=0 && t2>=0)
					{
						if(SRExitationTable[j][0]==t1 && SRExitationTable[j][1]==t2)
						{
							finalTable[i][4] = SRExitationTable[j][2];finalTable[i][5] = SRExitationTable[j][3];
						}
					}
					else
					{
						finalTable[i][4] = -1;finalTable[i][5] = -1;
					}
				}
			}
		}
	}
	else if(wanted + available == 7)/*single to single*/
	{
		int t1,t2;
		for(int i = 0; i < row; i++)
		{
			t1 = finalTable[i][1]; t2 = finalTable[i][2];
			for(int j = 0; j < 4 ; j++)
			{
				if(available == 3)
				{
					if(t1>=0 && t2>=0)
					{
						if(TExitationTable[j][0]==t1 && TExitationTable[j][1]==t2)
						{
							finalTable[i][3] = TExitationTable[j][2];
						}
					}
					else
					{
						finalTable[i][3] = -1;
					}
				}
				else
				{
					if(t1>=0 && t2>=0)
					{
						if(DExitationTable[j][0]==t1 && DExitationTable[j][1]==t2)
						{
							finalTable[i][3] = DExitationTable[j][2];
						}
					}
					else
					{
						finalTable[i][3] = -1;
					}
				}
			}
		}
	}
	else if(wanted < 3 && available > 2)/*double to single example JK to T*/
	{
		int t1,t2;
		for(int i = 0; i < row; i++)
		{
			t1 = finalTable[i][2]; t2 = finalTable[i][3];
			for(int j = 0; j < 4 ; j++)
			{
				if(available == 3)
				{
					if(t1>=0 && t2>=0)
					{
						if(TExitationTable[j][0]==t1 && TExitationTable[j][1]==t2)
						{
							finalTable[i][4] = TExitationTable[j][2];
						}
					}
					else
					{
						finalTable[i][4] = -1;
					}
				}
				else
				{
					if(t1>=0 && t2>=0)
					{
						if(DExitationTable[j][0]==t1 && DExitationTable[j][1]==t2)
						{
							finalTable[i][4] = DExitationTable[j][2];
						}
					}
					else
					{
						finalTable[i][4] = -1;
					}
				}
			}
		}
	}
	else/*single to double example T to JK*/
	{
		int t1,t2;
		for(int i = 0; i < row; i++)
		{
			t1 = finalTable[i][1]; t2 = finalTable[i][2];
			for(int j = 0; j < 4 ; j++)
			{
				if(available == 1)
				{
					if(t1>=0 && t2>=0)
					{
						if(JKExitationTable[j][0]==t1 && JKExitationTable[j][1]==t2)
						{
							finalTable[i][3] = JKExitationTable[j][2];finalTable[i][4] = JKExitationTable[j][3];
						}
					}
					else
					{
						finalTable[i][3] = -1;finalTable[i][4] = -1;
					}
				}
				else
				{
					if(t1>=0 && t2>=0)
					{
						if(SRExitationTable[j][0]==t1 && SRExitationTable[j][1]==t2)
						{
							finalTable[i][3] = SRExitationTable[j][2];finalTable[i][4] = SRExitationTable[j][3];
						}
					}
					else
					{
						finalTable[i][3] = -1;finalTable[i][4] = -1;
					}
				}
			}
		}
	}
	if(wanted == 1)
	{
		cout<<setw(6)<<"J";
		cout<<setw(6)<<"K";
		cout<<setw(6)<<"Q";
		cout<<setw(6)<<"Q(1)";
	}
	else if(wanted == 2)
	{
		cout<<setw(6)<<"S";
		cout<<setw(6)<<"R";
		cout<<setw(6)<<"Q";
		cout<<setw(6)<<"Q(1)";
	}
	else if(wanted == 3)
	{
		cout<<setw(6)<<"T";
		cout<<setw(6)<<"Q";
		cout<<setw(6)<<"Q(1)";
	}
	else
	{
		cout<<setw(6)<<"D";
		cout<<setw(6)<<"Q";
		cout<<setw(6)<<"Q(1)";
	}
	if(available == 1)
	{
		cout<<setw(6)<<"J";
		cout<<setw(6)<<"K";
	}
	else if(available == 2)
	{
		cout<<setw(6)<<"S";
		cout<<setw(6)<<"R";
	}
	else if(available == 3)
	{
		cout<<setw(6)<<"T";
	}
	else
	{
		cout<<setw(6)<<"D";
	}
	cout<<endl;
	for(int i = 0; i < row ; i++)
	{
		for(int j = 0; j < col ; j++)
		{
			if(finalTable[i][j]==-1)
				cout<<setw(6)<<"x";
			else
				cout<<setw(6)<<finalTable[i][j];
		}
		cout<<endl;
	}
	/*--------------------------------FlipFlip tables created--------------------------*/

	int noOfBits = 0;
	noOfBits = log2(row);
	/* Input is double in terms of flipflop Output is single in terms of flipflop*/
	/*-------------------------------------OR------------------------------------*/
	/* Input is single in terms of flipflop Output is single in terms of flipflop*/
	if((wanted < 3 && available >2)||((wanted == 3 && available == 4)||(wanted == 4 && available == 3)))
	{
		calculateOutput(noOfBits,1);
	}

	/* Input is single in terms of flipflop Output is double in terms of flipflop*/
	/*-------------------------------------OR------------------------------------*/
	/* Input is double in terms of flipflop Output is double in terms of flipflop*/
	else
	{
		calculateOutput(noOfBits,2);
	}
	return 0;
}

void calculateOutput(int noOfBits,int noOfOutput)
{
	for(int a = 0; a < noOfOutput; a++)
	{
		if(noOfOutput == 2 && a==0)
			cout<<"\n----------------------------------------Calculation for first variable----------------------------------------\n";
		else if(noOfOutput == 2 && a==1)
			cout<<"\n---------------------------------------Calculation for second variable----------------------------------------\n";
		cout<<"\n-------------------------------------List of all numbers taken from table-------------------------------------\n";
		int noOfOneDash,noOfTwoDash;
		QuineMccluskeyOutput* oneDash[row*2];
		QuineMccluskeyOutput* twoDash[row*2];
		QuineMccluskey* number[row];
		for(int i = 0 ; i < row ; i++ )
		{
			number[i] = new QuineMccluskey(noOfBits);
		}
		for(int i = 0 ; i < 15 ; i++ )
		{
			oneDash[i] = new QuineMccluskeyOutput(noOfBits);
		}
		for(int i = 0 ; i < 15 ; i++ )
		{
			twoDash[i] = new QuineMccluskeyOutput(noOfBits);
		}

		for(int i = 0 ; i < row ; i++)
		{
			number[i]->num = i;
			if(finalTable[i][col-a-1]==0)
			{
				number[i]->isZero = true;
			}
			else
			{
				number[i]->calcBinary();
				number[i]->isZero = false;
			}
			if(finalTable[i][col-a-1]>0)
			{
				number[i]->isPrime = true;
			}
			else
			{
				number[i]->isPrime = false;
			}
		}
		for(int i = 0 ; i < row ; i++ )
		{
			if(!number[i]->isZero)
			{
				number[i]->printData();
			}
		}
		cout<<"\n---------------------------------------List of all pairs of two numbers---------------------------------------\n";
		/* Data from First level QM goes to second level QM with 1 dash */
		for(int h = 0,i = 0 ; i < row ; i++ )
		{
			if(number[i]->isZero == true)
            {
                if(oneDash[i]->isEmpty)
					oneDash[i]->isEmpty = true;
                continue;
            }
			for(int j = 0 ; j < row ; j++)
			{
				if(i == j || number[i]->numOfOne == number[j]->numOfOne || number[j]->isZero == true)
				{
					if(oneDash[i]->isEmpty)
						oneDash[i]->isEmpty = true;
					continue;
				}
				else
				{
					int count = 0,pos = 0;
					for(int k = 0; k < noOfBits ; k++ )
					{
						if(number[i]->binary[k]!=number[j]->binary[k])
						{
							pos = k;
							count++;
						}
					}
					if(count == 1)
					{
						for(int l = 0 ; l < noOfBits ; l++)
						{
							oneDash[h]->binary[l] = number[i]->binary[l];
						}
						oneDash[h]->binary[pos] = -1;
						oneDash[h]->dashpos[0] = pos;
						oneDash[h]->isEmpty = false;
						oneDash[h]->noOfDash = 1;
						oneDash[h]->used = false;
						for(int l = 0, m = 0 ; m < 2 ; l++)
						{
							if(oneDash[h]->numused[l] == -10)
							{
								if(m == 0)
								{
									oneDash[h]->numused[l] = number[i]->num;
									number[i]->used = true;
									m++;
								}
								else
								{
									oneDash[h]->numused[l] = number[j]->num;
									number[j]->used = true;
									m++;
								}
							}
						}
						h++;
					}
					else
					{
						if(oneDash[h]->isEmpty)
						oneDash[h]->isEmpty = true;
					}
				}
			}
			noOfOneDash = h;
		}
		for(int i = 0; i < noOfOneDash ; i++)
		{
			for(int j = i; j <noOfOneDash ; j++)
			{
				if(i == j )
					continue;
				if((oneDash[i]->numused[0] == oneDash[j]->numused[0]) && (oneDash[i]->numused[1] == oneDash[j]->numused[1]) || (oneDash[i]->numused[0] == oneDash[j]->numused[1]) && (oneDash[i]->numused[1] == oneDash[j]->numused[0]) )
					oneDash[j]->isEmpty = true;
			}
		}
		for(int i = 0 ; i < noOfOneDash ; i++)
		{
			if(!oneDash[i]->isEmpty)
			{
				oneDash[i]->calcNoOfOne();
				oneDash[i]->printData();
			}

		}
		cout<<"\n--------------------------------------List of all pairs of four numbers---------------------------------------\n";
		if(noOfBits>2)
		{
			/* Data from second level QM goes to third level QM with 2 dash */
			for(int h = 0,i = 0 ; i < row ; i++ )
			{
				if(oneDash[i]->isEmpty == true)
	            {
	                if(twoDash[i]->isEmpty)
						twoDash[i]->isEmpty = true;
	                continue;
	            }
				for(int j = 0 ; j < noOfOneDash ; j++)
				{
					if(i == j || oneDash[i]->noOfOne == oneDash[j]->noOfOne || oneDash[j]->isEmpty == true)
					{
						if(twoDash[i]->isEmpty)
							twoDash[i]->isEmpty = true;
						continue;
					}
					else
					{
						int count = 0,pos = 0;
						for(int k = 0; k < 3 ; k++ )
						{
							if(oneDash[i]->binary[k]!=oneDash[j]->binary[k])
							{
								pos = k;
								count++;
							}
						}
						if(count == 1)
						{
							for(int l = 0 ; l < 3 ; l++)
							{
								twoDash[h]->binary[l] = oneDash[i]->binary[l];
							}
							twoDash[h]->binary[pos] = -1;
							twoDash[h]->dashpos[0] = oneDash[i]->dashpos[0];
							twoDash[h]->dashpos[1] = pos;
							twoDash[h]->isEmpty = false;
							twoDash[h]->noOfDash = 2;
							twoDash[h]->used = false;
							oneDash[i]->used = true;
							oneDash[j]->used = true;
							twoDash[h]->numused[0] = oneDash[i]->numused[0];
							twoDash[h]->numused[1] = oneDash[i]->numused[1];
							twoDash[h]->numused[2] = oneDash[j]->numused[0];
							twoDash[h]->numused[3] = oneDash[j]->numused[1];
							h++;
						}

						else
						{
							if(twoDash[h]->isEmpty)
								twoDash[h]->isEmpty = true;
						}
					}
				}
				noOfTwoDash = h;
			}
			for(int i = 0; i < noOfTwoDash ; i++)
			{
				for(int j = i; j <noOfTwoDash ; j++)
				{
					if(i == j )
						continue;
					else
					{
						int t1 = twoDash[i]->numused[0] + twoDash[i]->numused[1] + twoDash[i]->numused[2] + twoDash[i]->numused[3];
						int t2 = twoDash[j]->numused[0] + twoDash[j]->numused[1] + twoDash[j]->numused[2] + twoDash[j]->numused[3];
						if(t1 == t2)
							twoDash[j]->isEmpty = true;
					}
				}
			}
			for(int i = 0 ; i < noOfTwoDash ; i++)
			{
				if(twoDash[i]->isEmpty == false)
				{
					twoDash[i]->calcNoOfOne();
					twoDash[i]->printData();
				}

			}
		}
		int temp[row],count = 0;
		for(int i = 0 ; i < row ; i++)
		{
			if(number[i]->isPrime == true)
			{
				temp[i] = number[i]->num;
				count++;
			}
			else
			{
				temp[i] = 0;
			}
		}
		int primeImplecants[count][2];
		for(int i = 0 , j = 0 ; i < row ; i++ )
		{
			if(temp[i] != 0)
			{
				primeImplecants[j][0] = temp[i];
				primeImplecants[j][1] = 0;
				j++;
			}
		}
		cout<<"\n-----------------------------Unused Combination to be considered for next round-------------------------------\n";
		int noOfterms = 0;
		for(int i = 0 ; i < row ; i++)
		{
			if(number[i]->isZero == false)
			{
				if(number[i]->used == false)
				{
					number[i]->printData();
					noOfterms++;
				}
			}
		}
		for(int i = 0 ; i < noOfOneDash ; i++)
		{
			if(oneDash[i]->isEmpty == false)
			{
				if(oneDash[i]->used == false)
				{
					oneDash[i]->printData();
					noOfterms++;
				}
			}
		}
		if(noOfBits>2)
		{
			for(int i = 0 ; i < noOfTwoDash ; i++)
			{
				if(twoDash[i]->isEmpty == false)
				{
					if(twoDash[i]->used == false)
					{
						twoDash[i]->printData();
						noOfterms++;

					}
				}
			}
		}
		cout<<"\n-----------------------------------------------Prime Implicants-----------------------------------------------";
		cout<<"\nPrimeImplecants are:";
		for(int i = 0 ; i < count ; i++ )
		{
			if(i<count - 1)
				cout<<primeImplecants[i][0]<<", ";
			else
				cout<<primeImplecants[i][0];
		}
		QuineMccluskeyOutput* output[noOfterms];
		for(int i = 0 ; i < noOfterms ; i++)
		{
			output[i] = new QuineMccluskeyOutput(noOfBits);
		}
		int c = 0;
		for(int i = 0 ; i < row ; i++)
		{
			if(number[i]->isZero == false)
			{
				if(number[i]->used == false)
				{
					for(int j = 0 ; j < 3 ; j++)
					{
						output[c]->binary[j] = number[i]->binary[j];
					}
					for(int j = 0 ; j < 4 ; j++)
					{
						if(j == 0)
							output[c]->numused[j] = number[i]->num;
						else
							output[c]->numused[j] = -10;
					}
					c++;
				}
			}
		}
		for(int i = 0 ; i < noOfOneDash ; i++)
		{
			if(oneDash[i]->isEmpty == false)
			{
				if(oneDash[i]->used == false)
				{
					for(int j = 0 ; j < 3 ; j++)
					{
						output[c]->binary[j] = oneDash[i]->binary[j];
					}
					for(int j = 0 ; j < 4 ; j++)
					{
						if(j < 2)
							output[c]->numused[j] = oneDash[i]->numused[j];
						else
							output[c]->numused[j] = -10;
					}
					c++;
				}
			}
		}
		if(noOfBits > 2)
		{
			for(int i = 0 ; i < noOfTwoDash ; i++)
			{
				if(twoDash[i]->isEmpty == false)
				{
					if(twoDash[i]->used == false)
					{
						for(int j = 0 ; j < 3 ; j++)
						{
							output[c]->binary[j] = twoDash[i]->binary[j];
						}
						for(int j = 0 ; j < 4 ; j++)
						{
							output[c]->numused[j] = twoDash[i]->numused[j];
						}
						c++;
					}
				}
			}
		}
		bool found = false;
		for(int i = 0; i < noOfterms ; i++)
		{
			for(int j = 0 ; j < 4 ; j++)
			{
				for(int k = 0 ; k < count ; k++)
				{
					if(output[i]->numused[j] == primeImplecants[k][0])
						primeImplecants[k][1]++;
				}
			}
			for(int j = 0 ; j < count ; j++)
			{
				if(primeImplecants[j][1] > 0)
					found = true;
				else
				{
					found = false;
					break;
				}
			}
			if(found == true)
			{
				output[i]->used = true;
				break;
			}
			else
			{
				for(int k = 0 ; k < count ; k++)
				{
					primeImplecants[k][1] = 0;
				}
			}
		}

		if(found == false)
		{
			for(int i = 0; i < noOfterms ; i++)
			{
				if(i + 1 < noOfterms)
				{
					for(int j = 0 ; j < 4 ; j++)
					{
						for(int k = 0 ; k < count ; k++)
						{
							if(output[i]->numused[j] == primeImplecants[k][0])
								primeImplecants[k][1]++;
							if(output[i+1]->numused[j] == primeImplecants[k][0])
								primeImplecants[k][1]++;
						}
					}
					for(int j = 0 ; j < count ; j++)
					{
						if(primeImplecants[j][1] > 0)
							found = true;
						else
						{
							found = false;
							break;
						}
					}
					if(found == true)
					{
						output[i]->used = true;
						output[i+1]->used = true;
						break;
					}
					else
					{
						for(int k = 0 ; k < count ; k++)
						{
							primeImplecants[k][1] = 0;
						}
					}
				}
				else
				{
					for(int j = 0 ; j < 4 ; j++)
					{
						for(int k = 0 ; k < count ; k++)
						{
							if(output[i]->numused[j] == primeImplecants[k][0])
								primeImplecants[k][1]++;
							if(output[0]->numused[j] == primeImplecants[k][0])
								primeImplecants[k][1]++;
						}
					}
					for(int j = 0 ; j < count ; j++)
					{
						if(primeImplecants[j][1] > 0)
							found = true;
						else
						{
							found = false;
							break;
						}
					}
					if(found == true)
					{
						output[i]->used = true;
						output[0]->used = true;
						break;
					}
					else
					{
						for(int k = 0 ; k < count ; k++)
						{
							primeImplecants[k][1] = 0;
						}
					}
				}
			}
		}
		cout<<"\n------------------------------------------------Selected Terms------------------------------------------------\n";
		for(int i = 0 ; i < noOfterms ; i++ )
		{
			if(output[i]->used)
			{
				output[i]->printData();
			}
		}
		char out[3],ans;
		if(wanted == 1)
		{
			out[0] = 'J';out[1] = 'K';out[2] = 'Q';
		}
		else if(wanted == 2)
		{
			out[0] = 'S';out[1] = 'R';out[2] = 'Q';
		}
		else if(wanted == 3)
		{
			out[0] = 'T';out[1] = 'Q';
		}
		else
		{
			out[0] = 'D';out[1] = 'Q';
		}
		if(available == 1 && a == 0)
		{
			ans = 'K';
		}
		else if(available == 1 && a == 1)
		{
			ans = 'J';
		}
		else if(available == 2 && a == 0)
		{
			ans = 'R';
		}
		else if(available == 2 && a == 1)
		{
			ans = 'S';
		}
		else if(available ==3)
		{
			ans = 'T';
		}
		else
		{
			ans = 'D';
		}
		cout<<"\n-------------------------------------------------Final Output-------------------------------------------------\n";
		cout<<"                                                   ";
		cout<<ans<<" = ";
		bool tflaf = false;
		for(int i = 0 ; i < noOfterms ; i++ )
		{
			if(output[i]->used == true)
			{
				if(tflaf == true)
					cout<<" + ";
				for(int j = 0 ; j < noOfBits ; j++ )
				{
					if(output[i]->binary[j] == 1)
						cout<<out[j];
					else if(output[i]->binary[j] == 0)
						cout<<"~"<<out[j];
				}
				tflaf = true;
			}
		}
	}
}


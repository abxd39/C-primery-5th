class AB
{
    public string createString(int N,int K)
    {
        string str(N,'A');
		int tempN=N-1;
		int temp=0,bNumber=0;
        while(temp<K)
		{
			temp=temp-bNumber+tempN;
			bNumber++;
			tempN--;
		}
        
    }
}
        
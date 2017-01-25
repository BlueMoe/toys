template<class T>
inline vector<T> MaxSubSequenceSumSequence(vector<T> sequence)
{
	if (sequence.size() <= 1)	return sequence;
	
	vector<T>::iterator beg = sequence.begin();
	vector<T>::iterator end = sequence.begin();
	vector<T>::iterator tempBeg = sequence.begin();
	int sum = 0;
	int tempSum = 0;
	for (auto p = sequence.begin(); p != sequence.end(); ++p)
	{
		tempSum += *p;
		if (tempSum <= *p)
		{
			tempSum = *p;
			tempBeg = p;
		}
		if (tempSum >= sum)
		{
			sum = tempSum;
			beg = tempBeg;
			end = p;
		}
	}

	return vector<T>(beg, end + 1);
}


template<class Iter,class Predicate>
inline void quick_sort(Iter&& beg, Iter&& end, Predicate&& comp)
{
	quick_sort_impl(forward<Iter>(beg), forward<Iter>(end), forward<Predicate>(comp), iterator_traits<Iter>::iterator_category());
}

template<class Iter,class Predicate>
inline void quick_sort_impl(Iter&&  beg, Iter&&  end,Predicate&& comp, random_access_iterator_tag)
{
	if(beg >= end)	return;

	Iter i = beg;
	Iter j = end - 1;
	iterator_traits<Iter>::value_type key = *i;
	while(i < j)
	{
		while(i < j && comp(key,*j))  --j;
		*i = *j;
		while(i < j && comp(*i,key))  ++i;
		*j = *i;
	}
	*i = key;
	quick_sort_impl(forward<Iter>(beg),forward<Iter>(i),forward<Predicate>(comp), iterator_traits<Iter>::iterator_category());
	quick_sort_impl(forward<Iter>(i+1),forward<Iter>(end),forward<Predicate>(comp), iterator_traits<Iter>::iterator_category());
	
}

#include <iostream>

template<class T1, class T2>
class Link{
	T1 val;
	Link<T2, T1> *p;
public:
	friend Link<T2, T1>;

	Link() : p(nullptr) {}
	Link(T1 val) : val(val), p(nullptr) {}
	Link(const Link<T1, T2> &) = delete;
	~Link(){
		if(p) p->p = nullptr;
	}
	Link<T1, T2> &operator=(const Link<T1, T2> &) = delete;

	void link(Link<T2, T1> &l){
		p = &l;
		l.p = this;
	}

	operator T1(){
		return val;
	}

	Link<T1, T2> &operator=(const T1 &val){
		this->val = val;
		return *this;
	}

	Link<T2, T1> &operator*(){
		return *p;
	}

	friend void swap(Link<T1, T2> &l, Link<T1, T2> &r){
		std::swap(l.val, r.val);
		Link<T2, T1> *lp = l.p, *rp = r.p;
		if(r.p = lp) lp->p = &r;
		if(l.p = rp) rp->p = &l;
	}
};

int main(){
	{
		Link<int, int> a(1), b(2);
		std::cout << "a = " << a << ", b = " << b << std::endl;                        // a = 1, b = 2
		a.link(b);                                                                     // link a and b
		std::cout << "a = " << a << ", *a = " << *a << ", **a = " << **a << std::endl; // a = 1, *a = 2, **a = 1
		std::cout << "b = " << b << ", *b = " << *b << ", **b = " << **b << std::endl; // b = 2, *b = 1, **b = 2
		*a = 3;                                                                        // substitute 3 to *a (aka. b)
		std::cout << "b = " << b << std::endl;                                         // b = 3
		***b = 4;                                                                      // substitute 4 to ***b (aka. a)
		std::cout << "a = " << a << std::endl;                                         // a = 4
	}
	{
		Link<int, double> a(1), b(2);
		Link<double, int> c(3.0), d(4.0);

		a.link(c);
		b.link(d);
		/*
		 linked like:
		 a=1 --- c=3.0
		 b=2 --- d=4.0
		*/

		std::cout << "a = " << a << ", *a = " << *a << std::endl; // a = 1, *a = 3
		std::cout << "b = " << b << ", *b = " << *b << std::endl; // b = 2, *b = 4
		std::cout << "c = " << c << ", *c = " << *c << std::endl; // c = 3, *c = 1
		std::cout << "d = " << d << ", *d = " << *d << std::endl; // d = 4, *d = 2

		swap(a, b);
		/*
		 swapped like:
		 a=2   c=3.0
		    \ /
		     X
		    / \
		 b=1   d=4.0
		*/

		std::cout << "a = " << a << ", *a = " << *a << std::endl; // a = 2, *a = 4
		std::cout << "b = " << b << ", *b = " << *b << std::endl; // b = 1, *b = 3
		std::cout << "c = " << c << ", *c = " << *c << std::endl; // c = 3, *c = 1
		std::cout << "d = " << d << ", *d = " << *d << std::endl; // d = 4, *d = 2
	}
}

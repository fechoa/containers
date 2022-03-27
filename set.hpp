/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a1111 <a1111@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:02:24 by a1111             #+#    #+#             */
/*   Updated: 2022/01/31 19:36:57 by a1111            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include "rbtree.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include "algo.hpp"
# include <functional>
# include <memory>
# include "iterator_traits.hpp"
# include "pair.hpp"

namespace ft {
	template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
	class set
	{	
	public:
		typedef T																	value_type;
		typedef Compare																value_compare;
		typedef T 																	key_type;
		typedef Compare																key_compare;

		typedef Alloc																allocator_type;
		
		typedef typename allocator_type::reference 									reference;
		typedef typename allocator_type::const_reference							const_reference;
		typedef typename allocator_type::pointer									pointer;
		typedef typename allocator_type::const_pointer								const_pointer;
		
		typedef typename ft::RBTree<value_type, value_compare, allocator_type> 		rbtree;
		typedef typename ft::Node<value_type>										node;
		typedef node*																node_pointer;
		
		typedef RBTreeIterator<node_pointer, pointer>								iterator;
		typedef RBTreeIterator<node_pointer, const_pointer>							const_iterator;
		typedef RBTreeReverseIterator<iterator>										reverse_iterator;
		typedef RBTreeReverseIterator<const_iterator>								const_reverse_iterator;
		
		typedef typename iterator_traits<iterator>::difference_type					difference_type;
		typedef size_t																size_type;

	private:
		rbtree			_tree;

		allocator_type	_alloc;
		key_compare		_compare;

	public:
		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _tree(value_compare(comp), alloc), _alloc(alloc), _compare(comp){}
	
		template <typename InputIterator>
  		set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _tree(value_compare(comp), alloc),  _alloc(alloc), _compare(comp)
		{
			this->insert(first, last);
		}
		
		set (const set& cp)
		: _tree(value_compare(cp._compare), cp._alloc),  _alloc(cp._alloc), _compare(cp._compare)
		{
			*this = cp;
		}

		set& operator=(const set& cp)
		{
			if (this != &cp)
			{
				this->clear();
				this->_alloc = cp._alloc;
				this->_compare = cp._compare;
				this->insert(cp.begin(), cp.end());
			}
			return *this;
		}

		~set(void) {}

		iterator begin()
		{
			return (iterator(_tree.begin()));
		}
		const_iterator begin() const
		{
			return (const_iterator(_tree.begin()));
		}

		iterator end()
		{
			return (iterator(_tree.end()));
		}

		const_iterator end() const
		{
			return (const_iterator(_tree.end()));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}
		
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}
		
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}

		bool empty(void) const
		{
			return (this->size() == 0);
		}

		size_type size(void) const
		{
			return (_tree.size());
		}

		size_type max_size() const
		{
			return (std::min<size_type>(this->_alloc.max_size(), std::numeric_limits<difference_type>::max()));
		}

		void clear()
		{
			this->_tree.clear();
		}

		pair<iterator,bool> insert(const value_type& val)
		{
			iterator it = this->find(val);
			if (it == this->end())
			{
				this->_tree.insert(val);
				it = this->find(val);
				return pair<iterator,bool>(it, true);
			}
			return pair<iterator,bool>(it, false);
		}

		iterator insert(iterator position, const value_type& val)
		{
			position = this->find(val);
			if (position != this->end())
				return (position);
			this->insert(val);
			return (this->find(val));
		}
		
		template <typename InputIterator>
  		void insert(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		{
			for (; first != last; ++first)
				this->insert(*first);
		}

		void erase(iterator position)
		{
			if (this->find((*position)) != this->end())
				this->_tree.erase(*position);
		}

		size_type erase(const key_type& val)
		{
			iterator it = this->find(val);
			if (it != this->end())
			{
				this->erase(it);
				return (1);
			}
			return (0);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
		}

		iterator find(const key_type& val)
		{
			node_pointer tmp = this->_tree.findNode(val);
			if (!tmp)
				return this->end();
			return (iterator(tmp));
		}

		const_iterator find(const key_type& val) const
		{
			node_pointer tmp = this->_tree.findNode(val);
			if (!tmp)
				return this->end();
			return (const_iterator(tmp));
		}

		void swap(set& cp)
		{
			_tree.swap(cp._tree);
			std::swap(this->_compare, cp._compare);
			std::swap(this->_alloc, cp._alloc);
		}

		key_compare key_comp() const
		{
			return (this->_compare);
		}

		value_compare value_comp() const
		{
			return (this->_compare);
		}

		size_type count(const key_type& val) const
		{
			return (this->find(val) != this->end());
		}

		iterator lower_bound(const key_type& val)
		{
			return (_tree.lower_bound(val));
		}

		const_iterator lower_bound(const key_type& val) const
		{
			return (_tree.lower_bound(val));
		}

		iterator upper_bound(const key_type& val)
		{
			return (_tree.upper_bound(val));
		}

		const_iterator upper_bound(const key_type& val) const
		{
			return (_tree.upper_bound(val));
		}

		pair<const_iterator,const_iterator> equal_range(const key_type& val) const
		{
			return (pair<const_iterator,const_iterator>(lower_bound(val), upper_bound(val)));
		}

		pair<iterator,iterator> equal_range (const key_type& val)
		{
			return (pair<iterator,iterator>(lower_bound(val), upper_bound(val)));
		}

		allocator_type get_allocator() const
		{
			return  (this->_alloc);
		}		
	};

	template<typename T, typename Compare, typename Alloc>
	bool	operator==(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return (false);
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator!=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator<(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator<=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator>(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator>=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
	template<typename T, typename Compare, typename Alloc>
	void	swap(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y)
	{
		x.swap(y);
	}	

};

#endif
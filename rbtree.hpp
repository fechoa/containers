/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a1111 <a1111@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:18 by gkelsie           #+#    #+#             */
/*   Updated: 2022/01/31 20:22:28 by a1111            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <iostream>
# include <functional>
# include "iterator_traits.hpp"
# include "pair.hpp"


namespace ft
{
	template <typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	class iterator
	{
	public:
		typedef T					value_type;
		typedef Pointer				pointer;
		typedef Reference			reference;
		typedef Distance			difference_type;
		typedef Category			iterator_category;
	};

	template <typename Iter> 
	class RBTreeReverseIterator : public iterator<typename iterator_traits<Iter>::iterator_category,
					typename iterator_traits<Iter>::value_type, typename iterator_traits<Iter>::difference_type,
					typename iterator_traits<Iter>::pointer, typename iterator_traits<Iter>::reference>
	{
	public:
		typedef Iter														iterator_type;
		typedef typename iterator_traits<Iter>::pointer						pointer;
		typedef typename iterator_traits<Iter>::reference					reference;
		typedef typename iterator_traits<Iter>::difference_type				difference_type;


	protected:
		iterator_type _it;

	public:
		RBTreeReverseIterator()
		: _it(nullptr) {}

		RBTreeReverseIterator(iterator_type cp)
		: _it(cp) {}
	
		template <typename It>
		RBTreeReverseIterator(const RBTreeReverseIterator<It>& cp)
		: _it(cp.base()) {}

		iterator_type base() const
		{
			return (_it);
		}

		RBTreeReverseIterator operator+(difference_type n) const
		{
			return (RBTreeReverseIterator(_it - n));
		}
		
		RBTreeReverseIterator& operator++()
		{
			_it--;
			return (*this);
		}
		RBTreeReverseIterator operator++(int)
		{
			RBTreeReverseIterator tmp = *this;
			_it--;
			return (tmp);
		}
		
		RBTreeReverseIterator& operator+=(difference_type n)
		{
			_it -= n;
			return (*this);
		}
		
		RBTreeReverseIterator operator-(difference_type n) const
		{
			return (RBTreeReverseIterator(_it + n));
		}

		RBTreeReverseIterator& operator--()
		{
			_it++;
			return (*this);
		}
		RBTreeReverseIterator operator--(int)
		{
			RBTreeReverseIterator tmp = *this;
			_it++;
			return (tmp);
		}
		RBTreeReverseIterator& operator-=(difference_type n)
		{
			_it += n;
			return (*this);
		}

		reference operator*() const
		{
			iterator_type tmp = this->_it;
			tmp--;
			return (*tmp);
		}		

		pointer operator->() const
		{
			return (&(operator*()));
		}

		reference operator[](difference_type i) const
		{
			return (*(*this + i));
		}
	};

	template <typename It>
  	bool operator==(const RBTreeReverseIterator<It>& lhs, const RBTreeReverseIterator<It>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	
	template <typename It>
  	bool operator!=(const RBTreeReverseIterator<It>& lhs, const RBTreeReverseIterator<It>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	
	template <typename It>
  	bool operator<(const RBTreeReverseIterator<It>& lhs, const RBTreeReverseIterator<It>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	
	template <typename It>
  	bool operator<=(const RBTreeReverseIterator<It>& lhs,	const RBTreeReverseIterator<It>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	
	template <typename It>
	bool operator>(const RBTreeReverseIterator<It>& lhs, const RBTreeReverseIterator<It>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	
	template <typename It>
	bool operator>=(const RBTreeReverseIterator<It>& lhs, const RBTreeReverseIterator<It>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	
	template <typename It>
	RBTreeReverseIterator<It> operator+(typename RBTreeReverseIterator<It>::difference_type n, const RBTreeReverseIterator<It>& cp)
	{
		return (RBTreeReverseIterator<It>(cp - n));
	}
	
	template <typename It>
	typename RBTreeReverseIterator<It>::difference_type operator-(const RBTreeReverseIterator<It>& lhs, const RBTreeReverseIterator<It>& rhs)
	{
		return (lhs.base() - rhs.base());
	}


	enum Color {RED, BLACK};
	
	template <typename T>
	struct Node
	{
		typedef T	value_type; 
		
		value_type	_data;
		Color		_color;
		Node		*_left;
		Node		*_right;
		Node		*_parent;
		
		explicit Node(Color color = BLACK)
		: _data(nullptr), _color(color), _left(nullptr), _right(nullptr), _parent(nullptr) {}

		explicit Node(value_type cp)
		: _data(cp), _color(BLACK), _left(nullptr), _right(nullptr), _parent(nullptr) {}

		Node(const Node& cp)
		{
			*this = cp;
		}

		Node& operator=(const Node& cp)
		{
			if (this != &cp)
			{
				this->_data = cp._data;
				this->_color = cp._color;
				this->_left = cp._left;
				this->_right = cp._right;
				this->_parent = cp._parent;
			}
			return (*this);
		}

		~Node(void) {}
	};

	template <typename It, typename T>
	class RBTreeIterator : public iterator<std::bidirectional_iterator_tag, typename iterator_traits<T>::value_type>
	{
	public:
		typedef It 												iterator_type;
		typedef typename iterator_traits<T>::pointer			pointer;
		typedef typename iterator_traits<T>::reference			reference;
		typedef std::bidirectional_iterator_tag					iterator_category;
		typedef std::ptrdiff_t									difference_type;

	private:
		iterator_type _it;

	public:
		RBTreeIterator()
		: _it() {}

		RBTreeIterator(iterator_type cp)
		: _it(cp) {}
		
		template <typename Iter, typename I>
		RBTreeIterator(const RBTreeIterator<Iter, I>& cp)
		: _it(cp.base()) {}

		~RBTreeIterator()
		{}

		template <typename Iter, typename I>
		RBTreeIterator& operator=(const RBTreeIterator<Iter, I>& cp)
		{
			if (this != &cp)
				this->_it = cp.base();
			return (*this);
		}

		template <typename Iter, typename I>
  		bool operator==(const RBTreeIterator<I, Iter>& cp)
		{
			return (this->_it == cp.base());
		}
		
		template <typename Iter, typename I>
  		bool operator!=(const RBTreeIterator<I, Iter>& cp)
		{
			return (this->_it != cp.base());
		}		

		reference operator*() const
		{
			return (_it->_data);
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}

		RBTreeIterator& operator++()
		{
			this->_it = successor(this->_it);
			return (*this);
		}

		RBTreeIterator operator++(int)
		{
			RBTreeIterator tmp = *this;
			this->_it = successor(this->_it);
			return (tmp);
		}

		RBTreeIterator& operator--()
		{
			this->_it = predecessor(this->_it);
			return (*this);
		}

		RBTreeIterator operator--(int)
		{
			RBTreeIterator tmp = *this;
			this->_it = predecessor(this->_it);
			return (tmp);
		}

		iterator_type base() const
		{
			return (this->_it);
		}

	private:
		iterator_type minNodeElem(iterator_type elem)
		{
			while (elem->_left)
				elem = elem->_left;
			return (elem);
		}

		iterator_type maxNodeElem(iterator_type elem)
		{
			while (elem->_right)
				elem = elem->_right;
			return (elem);
		}	
	
		iterator_type successor(iterator_type elem)
		{
			iterator_type tmp = elem->_parent;
			
			if (elem->_right)
				return (minNodeElem(elem->_right));
			while (tmp && elem == tmp->_right)
			{
				elem = tmp;
				tmp = tmp->_parent;
			}
			return (tmp);
		}
		
		iterator_type predecessor(iterator_type elem)
		{
			iterator_type tmp = elem->_parent;
		
			if (elem->_left)
				return (maxNodeElem(elem->_left));
			while (tmp && elem == tmp->_left)
			{
				elem = tmp;
				tmp = tmp->_parent;
			}
			return (tmp);
		}
	};

	template <typename T, typename Compare = std::less<T> , typename Alloc = std::allocator<T> >
	class RBTree
	{
	public:
		typedef T															value_type;
		
		typedef typename Alloc::pointer										pointer;
		typedef typename Alloc::const_pointer								const_pointer;
		typedef typename Alloc::reference									reference;
		typedef typename Alloc::const_reference								const_reference;
		
		typedef struct Node<value_type>										node;
		typedef node*														node_pointer;
		typedef Compare														value_compare;
		
		typedef RBTreeIterator<node_pointer, pointer> 						iterator;
		typedef RBTreeIterator<node_pointer, const_pointer> 				const_iterator;
		typedef RBTreeReverseIterator<iterator> 							reverse_iterator;
		typedef RBTreeReverseIterator<const_iterator> 						const_reverse_iterator;
		
		typedef typename Alloc::template rebind<node>::other				allocator_type;
		typedef size_t														size_type;


	private:
		node_pointer		_root;
		node_pointer		_null;
		allocator_type		_alloc;
		value_compare		_compare;
		size_type			_size;


	public:
		RBTree(value_compare comp, allocator_type alloc)
		: _root(nullptr), _null(), _alloc(alloc), _compare(comp), _size(0)
		{
			_null = this->createNewNode();
		}

		RBTree(const RBTree& cp)
		: _root(nullptr), _null(), _alloc(cp._alloc), _compare(), _size(0)
		{
			*this = cp;
		}

		RBTree& operator=(RBTree& cp)
		{
			if (this != &cp)
			{
				iterator tmp = cp.begin();

				this->clear();
				value_comp() = cp.value_comp();
				this->_alloc = cp._alloc;

				while (tmp != cp.end())
					insert(*tmp++);
			}
			return (*this);
		}

		~RBTree(void)
		{
			this->clear();
			_alloc.destroy(this->_null);
			_alloc.deallocate(this->_null, 1);
		}

		void swap(RBTree& cp)
		{
			std::swap(this->_root, cp._root);
			std::swap(this->_null, cp._null);
			std::swap(this->_alloc , cp._alloc);
			std::swap(this->_compare, cp._compare);
			std::swap(this->_size, cp._size);
		}

		void clear(void)
		{
			this->destroy(this->_root);
			this->_size = 0;
			this->_root = nullptr;
		}

		size_type size(void) const
		{
			return (this->_size);
		}

		size_type max_size(void) const
		{
			return (_alloc.max_size());
		}

		iterator begin()
		{
			if (this->_root)
				return iterator(this->minNode(this->_root));
			return (iterator(this->_null));
		}
		
		const_iterator begin() const
		{
			if (this->_root)
				return const_iterator(this->minNode(this->_root));
			return (const_iterator(this->_null));
		}

		iterator end()
		{
			return (iterator(this->_null));
		}

		const_iterator end() const
		{
			return (const_iterator(this->_null));
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

		node_pointer findNode(const value_type& val) const
		{
			node_pointer tmp = this->_root;

			while (tmp)
			{
				if (!_compare(tmp->_data, val) && !_compare(val, tmp->_data))
					break;
				if (_compare(tmp->_data, val))
					tmp = tmp->_right;
				else
					tmp = tmp->_left;
			}
			return (tmp);
		}

		value_compare value_comp() const
		{
			return (this->_compare);
		}

		iterator lower_bound(const value_type& val)
		{
			node_pointer tmp = this->_root;
			node_pointer result = _null;
		
			while (tmp)
			{
				if (!_compare(tmp->_data, val))
				{
					result = tmp;
					tmp = tmp->_left;
				}
				else
					tmp = tmp->_right;
			}
			return (iterator(result));
		}

		const_iterator lower_bound(const value_type& val) const
		{
			node_pointer tmp = this->_root;
			node_pointer result = _null;
		
			while (tmp)
			{
				if (!_compare(tmp->_data, val))
				{
					result = tmp;
					tmp = tmp->_left;
				}
				else
					tmp = tmp->_right;
			}
			return (const_iterator(result));
		}

		iterator upper_bound(const value_type& val)
		{
			node_pointer tmp = this->_root;
			node_pointer result = _null;
			
			while (tmp)
			{
				if (_compare(val, tmp->_data))
				{
					result = tmp;
					tmp = tmp->_left;
				}
				else
					tmp = tmp->_right;
			}
			return (iterator(result));
		}

		const_iterator upper_bound(const value_type& val) const
		{
			node_pointer tmp = this->_root;
			node_pointer result = _null;
			
			while (tmp)
			{
				if (_compare(val, tmp->_data))
				{
					result = tmp;
					tmp = tmp->_left;
				}
				else
					tmp = tmp->_right;
			}
			return (const_iterator(result));
		}

	
		void insert(value_type val = value_type())
		{
			if (this->_root == nullptr)
			{
				this->_root = this->createNewNode(val);
				_root->_parent = this->_null;
				this->_null->_left = this->_root;
				this->_size++;
				return ;
			}
			if (findNode(val))
				return ;
			this->_null->_left = nullptr;
			_root->_parent = nullptr;
			node_pointer tmpNode = this->createNewNode(val);
			node_pointer parent = nullptr;
			node_pointer tmp = this->_root;
			while (tmp)
			{
				parent = tmp;
				if (_compare(tmpNode->_data, tmp->_data))
					tmp = tmp->_left;
				else
					tmp = tmp->_right;
				tmpNode->_parent = parent;
			}
			if (_compare(tmpNode->_data, parent->_data))
				parent->_left = tmpNode;
			else
				parent->_right = tmpNode;
			tmpNode->_color = RED;
			this->insertBalance(tmpNode);
			this->_null->_left = this->_root;
			this->_root->_parent = this->_null;
			this->_size++;
		}

		void erase(value_type val = value_type())
		{
			node_pointer delNode;
			node_pointer tmp;
			if (!this->_root || (delNode = this->findNode(val)) == nullptr)
				return ;
			this->_null->_left = nullptr;
			this->_root->_parent = nullptr;
			node_pointer tmpTwo = delNode;
			bool delColor = tmpTwo->_color;
			if (delNode->_left == nullptr)
			{
				tmp = delNode->_right;
				this->shiftNode(delNode, delNode->_right);
				_alloc.destroy(delNode);
				_alloc.deallocate(delNode, 1);
			}
			else if (delNode->_right == nullptr)
			{

				tmp = delNode->_left;
				this->shiftNode(delNode, delNode->_left);
				_alloc.destroy(delNode);
				_alloc.deallocate(delNode, 1);
			}
			else
			{
				tmpTwo = minNode(delNode->_right);
				delColor = tmpTwo->_color;
				tmp = tmpTwo->_right;
				if (tmpTwo->_parent != nullptr && tmpTwo->_parent != delNode)
				{
					this->shiftNode(tmpTwo, tmpTwo->_right);
					tmpTwo->_right = delNode->_right;
					tmpTwo->_right->_parent = tmpTwo;
				}
				this->shiftNode(delNode, tmpTwo);
				tmpTwo->_left = delNode->_left;
				tmpTwo->_left->_parent = tmpTwo;
				tmpTwo->_color = delNode->_color;
				_alloc.destroy(delNode);
				_alloc.deallocate(delNode, 1);
			}
			if (delColor == BLACK && tmp != nullptr)
				this->deleteBalance(tmp);
			if (this->_root != nullptr)
			{
				this->_null->_left = this->_root;
				this->_root->_parent = this->_null;
			}
			this->_size--;
		}

		node_pointer minNode(node_pointer elem) const
		{
			while (elem->_left)
				elem = elem->_left;
			return (elem);
		}

		node_pointer maxNode(node_pointer elem) const
		{
			while (elem->_right)
				elem = elem->_right;
			return (elem);
		}

		node_pointer successor(node_pointer elem)
		{
			node_pointer tmp = elem->_parent;
			
			if (elem->_right)
				return (minNode(elem->_right));
			while (tmp && elem == tmp->_right)
			{
				elem = tmp;
				tmp = tmp->_parent;
			}
			return (tmp);
		}

		node_pointer predecessor(node_pointer elem)
		{
			node_pointer tmp = elem->_parent;
			if (elem->_left)
				return (maxNode(elem->_left));
			while (tmp && elem == tmp->_left)
			{
				elem = tmp;
				tmp = tmp->_parent;
			}
			return (tmp);
		}

	private:	
		node_pointer createNewNode(value_type val = value_type())
		{
			node_pointer newNode = _alloc.allocate(1);
			_alloc.construct(newNode, val);
			return (newNode);
		}

		void insertBalance(node_pointer elem)
		{
			while (elem->_parent && elem->_parent->_color == RED)
			{
				if (elem->_parent == elem->_parent->_parent->_left)
				{
					node_pointer brother = elem->_parent->_parent->_right;
					if (brother && brother->_color == RED)
					{
						elem->_parent->_color = BLACK;
						brother->_color = BLACK;
						elem->_parent->_parent->_color = RED;
						elem = elem->_parent->_parent;
					}
					else
					{
						if (elem == elem->_parent->_right)
						{
							elem = elem->_parent;
							this->leftRotate(elem);
						}
						elem->_parent->_color = BLACK;
						elem->_parent->_parent->_color = RED;
						this->rightRotate(elem->_parent->_parent);
						break ;
					}
				}
				else
				{
					node_pointer brother = elem->_parent->_parent->_left;
					if (brother && brother->_color == RED)
					{
						elem->_parent->_color = BLACK;
						brother->_color = BLACK;
						elem->_parent->_parent->_color = RED;
						elem = elem->_parent->_parent;
					}
					else
					{
						if (elem == elem->_parent->_left)
						{
							elem = elem->_parent;
							this->rightRotate(elem);
						}
						elem->_parent->_color = BLACK;
						elem->_parent->_parent->_color = RED;
						this->leftRotate(elem->_parent->_parent);
						break ;
					}
				}
			}
			this->_root->_color = BLACK;
		}

		void leftRotate(node_pointer elem)
		{
			node_pointer tmp = elem->_right;
			elem->_right = tmp->_left;
			if (tmp->_left)
				tmp->_left->_parent = elem;
			tmp->_parent = elem->_parent;
			if (!elem->_parent)
				this->_root = tmp;
			else if (elem == elem->_parent->_left)
				elem->_parent->_left = tmp;
			else
				elem->_parent->_right = tmp;
			tmp->_left = elem;
			elem->_parent = tmp;
		}

		void rightRotate(node_pointer elem)
		{
			node_pointer tmp = elem->_left;
			elem->_left = tmp->_right;
			if (tmp->_right)
				tmp->_right->_parent = elem;
			tmp->_parent = elem->_parent;
			if (!elem->_parent)
				this->_root = tmp;
			else if (elem == elem->_parent->_right)
				elem->_parent->_right = tmp;
			else
				elem->_parent->_left = tmp;
			tmp->_right = elem;
			elem->_parent = tmp; 
		}

		void destroy(node_pointer elem)
		{
			if (elem)
			{
				destroy(elem->_left);
				destroy(elem->_right);
				this->_alloc.destroy(elem);
				this->_alloc.deallocate(elem, 1);
			}
		}

		void shiftNode(node_pointer one, node_pointer two)
		{
			if (!one->_parent)
				this->_root = two;
			else if (one == one->_parent->_left)
				one->_parent->_left = two;
			else
				one->_parent->_right = two;
			if (two)
				two->_parent = one->_parent;
		}

		void deleteBalance(node_pointer elem)
		{
			while (elem != this->_root && elem->_color == BLACK)
			{
				if (elem && elem == elem->_parent->_left)
				{
					node_pointer brother = elem->_parent->_right;
					if (brother && brother->_color == RED)
					{
						brother->_color = BLACK;
						elem->_parent->_color = RED;
						this->leftRotate(elem->_parent);
						brother = elem->_parent->_right;
					}
					if (brother && brother->_color == BLACK
						&& brother->_left->_color == BLACK
						&& brother->_right->_color == BLACK)
					{
						brother->_color = RED;
						elem = elem->_parent;
					}
					else
					{
						if (brother->_right->_color == BLACK)
						{
							brother->_left->_color = BLACK;
							brother->_color = RED;
							this->rightRotate(brother);
						}
						brother->_color = elem->_parent->_color;
						elem->_parent->_color = BLACK;
						brother->_right->_color = BLACK;
						this->leftRotate(elem->_parent);
						elem = this->_root;
					}
				}
				else
				{
					node_pointer brother = elem->_parent->_left;
					if (brother && brother->_color == RED)
					{
						brother->_color = BLACK;
						elem->_parent->_color = RED;
						this->rightRotate(elem->_parent);
						brother = elem->_parent->_left;
					}
					if (brother && brother->_color == BLACK
						&& brother->_right->_color == BLACK
						&& brother->_left->_color == BLACK)
					{
						brother->_color = RED;
						elem = elem->_parent;
					}
					else
					{
						if (brother->_left->_color == BLACK)
						{
							brother->_right->_color = BLACK;
							brother->_color = RED;
							this->leftRotate(brother);
						}
						brother->_color = elem->_parent->_color;
						elem->_parent->_color = BLACK;
						brother->_left->_color = BLACK;
						this->rightRotate(elem->_parent);
						elem = this->_root;
					}
				}
			}
			elem->_color = BLACK;
		}
	};
};

#endif
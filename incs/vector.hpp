/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:08:05 by jasong            #+#    #+#             */
/*   Updated: 2022/12/23 17:58:15 by jasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>

namespace ft {
	template <
		class T, class Alloc = std::allocator<T> // generic template
	> class vector {
		private:

		public:
			vector() {
				std::cout << "vector constructor called" << std::endl;
			};
			~vector() {
				std::cout << "vector destructor called" << std::endl;
			}
	};
}

#endif
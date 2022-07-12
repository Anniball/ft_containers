/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:02:21 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/12 16:52:53 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

namespace ft
{
	class red_black_tree
	{
		/*
			---RULES---
			balanced binary tree rules :
				-each node can have until 2 subtrees :
					-left items are smaller
					-right items are larger
			red black tree rules :
			  	-a node is black or red
				-NIL are black
				-if a node is red its children are black
				-all path from a node to leaves contain same amount of black nodes
			red black tree subrules
				-nodes need one storage bit to keep track of color
				-longest path from root in no more twice the length of sorthest path
					-direct consequence : shortest path is all black nodes and longest is alternating red and black
		*/
		/*
			---SEARCH---
			Just iterate or :
			First rule: The first node in the tree is the leftmost node in the tree.
			Next rule: The successor of a node is:
				Next-R rule: If it has a right subtree, the leftmost node in the right subtree.
				Next-U rule: Otherwise, traverse up the tree
					If you make a right turn (i.e. this node was a left child), then that parent node is the successor
					If you make a left turn (i.e. this node was a right child), continue going up.
					If you can't go up anymore, then there's no successor
			https://stackoverflow.com/questions/2942517/how-do-i-iterate-over-binary-tree
		*/
		/*
			---ROTATIONS---
			-Rearrange subtrees (not a simple "rotation")
			-Goal is to decrease height of the tree
				-larger subtrees up, smaller subtrees down
			-Does not affect the order of elements

			Left Rotate Pseudo-Code :
			y = x.right
			x.right = y.left
			if y.left != T.nil
				y.left.p = x
			y.p = x.p
			if x.p == T.nil
				T.root = y
			else if x == x.p.left
				x.p.left = y
			else
				x.p.right = y
			y.left = x
			x.p = y
		*/
		/*
			---INSERT---
			Steps :
				-Insert Z and color it red
				-Recolor and rotate nodes to fix violation
			Scenarios to fix violation (where Z is the node posing problem):
				-Z = root -> color black
				-Z.uncle = red -> recolor
				-Z.uncle = black (triangle) -> rotate Z.parent //in opposite direction of Z I think?
				-Z.uncle = black (line) -> rotate Z.grandparent + recolor //in opposite direction of Z I think?
			Personal Note : A violation fixing can cause another violation, loop over the violation fixing while changing Z each time! 

			Simple Insert Pseudo-Code :
			y = T.nil
			x = T.root
			while x != T.nil
				y = x
				if z.key < x.key
					x = x.left
				else
					x = x.right
			z.p = y
			if y == T.nil
				T.root = z
			else if z.key < y.key
				y.left = z
			else
				y.right = z
			z.left = T.nil
			z.right = T.nil
			z.color = RED
			RB-INSERT-FIXUP(z) (Next Pseudo-Code)

			Case 4 Fix Violation Scenario Pseudo-Code
			while z.p.color == RED
				if z.p == z.p.p.left
					y = z.p.p.right
					if y.color == RED
						z.p.color = BLACK
						y.color = BLACK
						z.p.p.color = RED
						z = z.p.p
					else if z == z.p.right
						z = z.p
						LEFT-ROTATE(z)
					z.p.color = BLACK
					z.p.p.color = RED
					RIGHT-ROTATE(z.p.p)
				else (same but echange left and right)
			T.root.color = BLACK (Case 0)
			http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
		*/
	};
}


#endif
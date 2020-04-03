using System;
using System.Collections;
using System.Collections.Generic;

namespace RedBlackTree
{
    public class RedBlackTree<T> : ICollection<T> where T : IComparable<T>
    {
        private enum NodeColor
        {
            Red,
            Black
        }

        private class Node
        {
            public T Value { get; set; }
            public NodeColor Color { get; set; }

            public Node(T value)
            {
                Value = value;
                Color = NodeColor.Red;
            }

            public Node Left { get; set; }
            public Node Right { get; set; }

            public Node RotateRight()
            {
                var leftChild = Left;
                Left = leftChild.Right;
                leftChild.Right = this;
                leftChild.Color = Color;
                Color = NodeColor.Red;
                return leftChild;
            }

            public Node RotateLeft()
            {
                var rightChild = Right;
                Right = rightChild.Left;
                rightChild.Left = this;
                rightChild.Color = Color;
                Color = NodeColor.Red;
                return rightChild;
            }

            public void FlipColors()
            {
                Color = NodeColor.Red;

                if (Left != null)
                {
                    Left.Color = NodeColor.Black;
                }

                if (Right != null)
                {
                    Right.Color = NodeColor.Black;
                }
            }
        }

        private Node root;

        public int Count { get; private set; }

        public bool IsReadOnly => false;

        public T Min => FindMin(root).Value;

        public T Max => FindMax(root).Value;

        private static bool IsRed(Node node) => node != null && node.Color == NodeColor.Red;

        public void Add(T value)
        {
            root = Insert(root, value);
            if (IsRed(root))
            {
                root.Color = NodeColor.Black;
            }
        }

        private Node Insert(Node node, T value)
        {
            if (node == null)
            {
                node = new Node(value);
                Count++;
            }

            if (IsRed(node.Left) && IsRed(node.Right))
            {
                node.FlipColors();
            }

            var comp = value.CompareTo(node.Value);
            if (comp < 0)
            {
                node.Left = Insert(node.Left, value);
            }
            else if (comp > 0)
            {
                node.Right = Insert(node.Right, value);
            }
            else
            {
                node.Value = value;
            }

            if (!IsRed(node.Left) && IsRed(node.Right))
            {
                node = node.RotateLeft();
            }

            if (IsRed(node.Left) && IsRed(node.Left.Left))
            {
                node = node.RotateRight();
            }

            return node;
        }

        private static Node FixUp(Node node)
        {
            if (!IsRed(node.Left) && IsRed(node.Right))
            {
                node = node.RotateLeft();
            }

            if (IsRed(node.Left) && IsRed(node.Left?.Left))
            {
                node = node.RotateRight();
            }

            if (IsRed(node.Left) && IsRed(node.Right))
            {
                node.FlipColors();
            }

            return node;
        }

        private static Node DeleteMin(Node node)
        {
            if (node.Left == null)
            {
                return null;
            }

            if (!IsRed(node.Left) && !IsRed(node.Left.Left))
            {
                node = MoveRedLeft(node);
            }

            node.Left = DeleteMin(node.Left);

            return FixUp(node);
        }

        private static Node MoveRedLeft(Node node)
        {
            node.FlipColors();
            if (IsRed(node?.Right?.Left))
            {
                node.Right = node.Right.RotateRight();
                node = node.RotateLeft();
                node.FlipColors();
            }
            return node;
        }

        private static Node MoveRedRight(Node node)
        {
            node.FlipColors();
            if (IsRed(node.Left?.Left))
            {
                node = node.RotateRight();
                node.FlipColors();
            }
            return node;
        }

        public bool Remove(T value)
        {
            bool isFounded = default;
            root = Delete(root, value, ref isFounded);
            if (isFounded)
            {
                Count--;
            }
            return isFounded;
        }

        private static Node Delete(Node node, T value, ref bool isFounded)
        {
            if (node == null)
            {
                isFounded = true;
                return null;
            }

            if (value.CompareTo(node.Value) < 0)
            {
                if (!IsRed(node?.Left) && !IsRed(node?.Left?.Left))
                {
                    node = MoveRedLeft(node);
                }
                node.Left = Delete(node.Left, value, ref isFounded);
            }
            else
            {
                if (IsRed(node.Left))
                {
                    node = node.RotateRight();
                }
                if (value.CompareTo(node.Value) == 0 && node.Right == null)
                {
                    isFounded = true;
                    return null;
                }
                if (!IsRed(node.Right) && !IsRed(node.Right?.Left))
                {
                    node = MoveRedRight(node);
                }
                if (value.CompareTo(node.Value) == 0)
                {
                    isFounded = true;
                    node.Value = FindMin(node.Right).Value;
                    node.Right = DeleteMin(node.Right);
                }
                else
                {
                    node.Right = Delete(node.Right, value, ref isFounded);
                }
            }
            return FixUp(node);
        }

        private static Node FindMin(Node node)
        {
            var min = node;
            while (min?.Left != null)
            {
                min = min.Left;
            }
            return min;
        }

        private static Node FindMax(Node node)
        {
            var max = node;
            while (max?.Right != null)
            {
                max = max.Right;
            }
            return max;
        }

        public T Find(T item)
        {
            var temp = root;
            while (temp != null)
            {
                var comp = item.CompareTo(temp.Value);
                if (comp == 0)
                {
                    return temp.Value;
                }
                else
                {
                    temp = comp > 0 ? temp.Right : temp.Left;
                }
            }

            return default;
        }

        public void Clear()
        {
            Count = 0;
            root = null;
        }

        public bool Contains(T item) => Find(item).CompareTo(item) == 0;

        public void CopyTo(T[] array, int arrayIndex)
        {
            var iter = GetEnumerator();
            iter.MoveNext();
            for (int i = arrayIndex; i < array.Length; i++)
            {
                array[i] = iter.Current;
                iter.MoveNext();
            }
        }

        public IEnumerator<T> GetEnumerator() => Iterate(root).GetEnumerator();

        private static IEnumerable<T> Iterate(Node node)
        {
            if (node.Left != null)
            {
                foreach (var item in Iterate(node.Left))
                {
                    yield return item;
                }
            }

            yield return node.Value;

            if (node.Right != null)
            {
                foreach (var item in Iterate(node.Right))
                {
                    yield return item;
                }
            }
        }

        public T this[int index] => ElementAt(index);

        public T ElementAt(int index)
        {
            var iter = GetEnumerator();
            iter.MoveNext();
            for (int i = 0; i < index; i++)
            {
                iter.MoveNext();
            }
            return iter.Current;
        }

        IEnumerator IEnumerable.GetEnumerator() => throw new NotImplementedException();
    }
}
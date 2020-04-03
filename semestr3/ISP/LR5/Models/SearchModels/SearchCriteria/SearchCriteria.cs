using System;

namespace Models
{
    [Serializable]
    public class SearchCriteria
    {
        public int Amount { get; set; }

        public SortParameter SortParameter { get; set; }

        public Order Order { get; set; }
    }
}

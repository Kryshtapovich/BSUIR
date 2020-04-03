using System;
using System.Collections.Generic;

namespace LR2
{
    [Serializable]
    public class ConfigurationOptions
    {
        public List<Folder> Folders { get; set; } = new List<Folder>();

        public CryptoSettings CryptoOption { get; set; } = new CryptoSettings();
    }
}

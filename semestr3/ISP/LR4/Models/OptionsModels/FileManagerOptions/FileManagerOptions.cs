using System;
using System.Collections.Generic;

namespace Models
{
    [Serializable]
    public class FileManagerOptions
    {
        public List<Folder> Folders { get; set; } = new List<Folder>();
                
        public string this[string folderName]
        {
            get
            {
                return Folders.Find(x => x.Name == folderName).Path;
            }
        }
    }
}

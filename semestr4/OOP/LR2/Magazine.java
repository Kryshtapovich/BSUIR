package com.company;

public class Magazine extends Post
{
    public Magazine(String name)
    {
        super(name);
        type = PostType.MAGAZINE;
    }
}

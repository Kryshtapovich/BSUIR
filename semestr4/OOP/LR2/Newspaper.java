package com.company;

public class Newspaper extends Post
{
    public Newspaper(String name)
    {
        super(name);
        type = PostType.NEWSPAPER;
    }
}

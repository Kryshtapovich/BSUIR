package com.company;

public abstract class Post
{
    private String name;

    protected PostType type;

    public Post(String name)
    {
        this.name = name;
    }

    public String getName()
    {
        return name;
    }

    public PostType getType()
    {
        return type;
    }
}

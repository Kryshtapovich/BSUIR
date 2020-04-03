package com.company;

import java.util.ArrayList;

public class PostSubscriber implements Subscriber
{
    private SubscriptionType type;

    private String name;

    private ArrayList<Post> subscriptions = new ArrayList<>();

    public PostSubscriber(String name, SubscriptionType type)
    {
        this.name = name;
        this.type = type;
    }

    @Override
    public void update(Post post)
    {
        if(post.getType().name() == this.type.name() ||
                this.type.name() == SubscriptionType.ULTIMATE.name())
        {
            System.out.println("- There is a new " + post.getClass().getSimpleName() +
                    " " + post.getName() + " for you, " + name + "\n");
            subscriptions.add(post);
        }
    }

    public String getPost()
    {
        String res = name + "'s post:\n";
        for (int i =0 ; i < subscriptions.size(); i++)
        {
            res += (i + 1) + " " + subscriptions.get(i).getName() + "\n";
        }
        return res;
    }
}

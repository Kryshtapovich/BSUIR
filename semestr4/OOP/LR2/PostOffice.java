package com.company;

import java.util.ArrayList;

public class PostOffice
{
    private ArrayList<Subscriber> subscribers = new ArrayList<>();

    public void subscribe(Subscriber subscriber)
    {
        subscribers.add(subscriber);
    }

    public void unsubscribe(Subscriber subscriber)
    {
        subscribers.remove(subscriber);
    }

    public void sendPost(Post post)
    {
        for (Subscriber subscriber: subscribers)
        {
            subscriber.update(post);
        }
    }

    public static void main(String[] args)
    {
        PostOffice postOffice = new PostOffice();

        PostSubscriber sub1 = new PostSubscriber("Bob", SubscriptionType.NEWSPAPER);
        PostSubscriber sub2 = new PostSubscriber("Mark", SubscriptionType.ULTIMATE);
        PostSubscriber sub3 = new PostSubscriber("Paul", SubscriptionType.MAGAZINE);

        postOffice.subscribe(sub1);
        postOffice.subscribe(sub2);
        postOffice.subscribe(sub3);

        postOffice.sendPost(new Magazine("T-Magazine"));
        postOffice.sendPost(new Magazine("Cosmopolitan"));
        postOffice.sendPost(new Newspaper("The New-York Times"));

        postOffice.unsubscribe(sub2);

        postOffice.sendPost(new Newspaper("Washington Post"));
        postOffice.sendPost(new Magazine("Men's Health"));

        System.out.println(sub1.getPost());
        System.out.println(sub2.getPost());
        System.out.println(sub3.getPost());
    }
}

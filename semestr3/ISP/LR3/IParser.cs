namespace LR2
{
    interface IParser
    {
        T Parse<T>() where T : new();
    }
}

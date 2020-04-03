namespace ConfigurationManager
{
    interface IParser
    {
        T Parse<T>() where T : new();
    }
}

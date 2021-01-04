using System.Collections;
using System.Collections.Generic;

#nullable disable

namespace PowerRonin.Json.Bson
{
    internal abstract class BsonToken
    {
        public abstract BsonType Type { get; }
        public BsonToken Parent { get; set; }
        public int CalculatedSize { get; set; }
    }

    internal class BsonObject : BsonToken, IEnumerable<BsonProperty>
    {
        private readonly List<BsonProperty> _children = new();

        public override BsonType Type => BsonType.Object;

        public IEnumerator<BsonProperty> GetEnumerator()
        {
            return _children.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Add(string name, BsonToken token)
        {
            _children.Add(new BsonProperty {Name = new BsonString(name, false), Value = token});
            token.Parent = this;
        }
    }

    internal class BsonArray : BsonToken, IEnumerable<BsonToken>
    {
        private readonly List<BsonToken> _children = new();

        public override BsonType Type => BsonType.Array;

        public IEnumerator<BsonToken> GetEnumerator()
        {
            return _children.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Add(BsonToken token)
        {
            _children.Add(token);
            token.Parent = this;
        }
    }

    internal class BsonEmpty : BsonToken
    {
        public static readonly BsonToken Null = new BsonEmpty(BsonType.Null);
        public static readonly BsonToken Undefined = new BsonEmpty(BsonType.Undefined);

        private BsonEmpty(BsonType type)
        {
            Type = type;
        }

        public override BsonType Type { get; }
    }

    internal class BsonValue : BsonToken
    {
        public BsonValue(object value, BsonType type)
        {
            Value = value;
            Type = type;
        }

        public object Value { get; }

        public override BsonType Type { get; }
    }

    internal class BsonBoolean : BsonValue
    {
        public static readonly BsonBoolean False = new(false);
        public static readonly BsonBoolean True = new(true);

        private BsonBoolean(bool value)
            : base(value, BsonType.Boolean)
        {
        }
    }

    internal class BsonString : BsonValue
    {
        public BsonString(object value, bool includeLength)
            : base(value, BsonType.String)
        {
            IncludeLength = includeLength;
        }

        public int ByteCount { get; set; }
        public bool IncludeLength { get; }
    }

    internal class BsonBinary : BsonValue
    {
        public BsonBinary(byte[] value, BsonBinaryType binaryType)
            : base(value, BsonType.Binary)
        {
            BinaryType = binaryType;
        }

        public BsonBinaryType BinaryType { get; set; }
    }

    internal class BsonRegex : BsonToken
    {
        public BsonRegex(string pattern, string options)
        {
            Pattern = new BsonString(pattern, false);
            Options = new BsonString(options, false);
        }

        public BsonString Pattern { get; set; }
        public BsonString Options { get; set; }

        public override BsonType Type => BsonType.Regex;
    }

    internal class BsonProperty
    {
        public BsonString Name { get; set; }
        public BsonToken Value { get; set; }
    }
}
# Architecture

- DataNode (holds data and types)
    - DataTypes/MetaTag
- Tree<T> (parent, children, data)
    - T = DataNode (usually)

- IParser
    - DOES NOT use Streams API
        - Why? Google Style Guide and International string support...

- IEnvironment
    - HashMap( Symbol ==> Tree<T> )
    


- Parser
- Environment

- Tree<DataNode>
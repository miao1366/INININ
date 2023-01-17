1. 
class CBlockUndo
{
public:
    std::vector<CTxUndo> vtxundo; // for all but the coinbase

    template<typename Stream> void Serialize(Stream& s) const { 
        static_assert(std::is_same<const cls&, decltype(*this)>::value, "Serialize type mismatch"); 
        Ser(s, *this); } 
    template<typename Stream> void Unserialize(Stream& s) { 
        static_assert(std::is_same<cls&, decltype(*this)>::value, "Unserialize type mismatch"); 
        Unser(s, *this); } 

    template<typename Stream> static void Ser(Stream& s, const cls& obj) { 
        SerializationOps(obj, s, CSerActionSerialize()); 
    } 
    template<typename Stream> static void Unser(Stream& s, cls& obj) { 
        SerializationOps(obj, s, CSerActionUnserialize()); 
    } 
    template<typename Stream, typename Type, typename Operation> 
    static inline void SerializationOps(Type& obj, Stream& s, Operation ser_action)
    {
        (::SerReadWriteMany(s, ser_action, obj.vtxundo))
    }

};
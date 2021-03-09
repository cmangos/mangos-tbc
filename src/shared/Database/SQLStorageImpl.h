/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef SQLSTORAGE_IMPL_H
#define SQLSTORAGE_IMPL_H

#include "ProgressBar.h"
#include "Log.h"
#include "DBCFileLoader.h"
#include <string>

template<class DerivedLoader, class StorageClass>
template<class S, class D>                                  // S source-type, D destination-type
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::convert(uint32 /*field_pos*/, S src, D& dst)
{
#if defined(__arm__)
    if (((unsigned) &dst) % sizeof(D)) {
       //The address is not aligned. Use memcpy to avoid ARM unaligned trap
       D converted(src);
       memcpy((void*) &dst, (void*) &converted, sizeof(D));
    }
    else
#endif
    dst = D(src);
}

template<class DerivedLoader, class StorageClass>
template<class S>                                           // S source-type
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::convert_to_bool(uint32 /*field_pos*/, S src, bool& dst)
{
    dst = (src != 0);
}

template<class DerivedLoader, class StorageClass>

void SQLStorageLoaderBase<DerivedLoader, StorageClass>::convert_str_to_str(uint32 /*field_pos*/, char const* src, char*& dst)
{
    if (!src)
    {
        dst = new char[1];
        *dst = 0;
    }
    else
    {
        uint32 l = strlen(src) + 1;
        dst = new char[l];
        memcpy(dst, src, l);
    }
}

template<class DerivedLoader, class StorageClass>
template<class S>                                           // S source-type
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::convert_to_str(uint32 /*field_pos*/, S /*src*/, char*& dst)
{
    dst = new char[1];
    *dst = 0;
}

template<class DerivedLoader, class StorageClass>
template<class D>                                           // D destination-type
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::convert_from_str(uint32 /*field_pos*/, char const* /*src*/, D& dst)
{
#if defined(__arm__)
    if (((unsigned) &dst) % sizeof(D)) {
       //The address is not aligned. Use memcpy to avoid ARM unaligned trap
       D converted(0);
       memcpy((void*) &dst, (void*) &converted, sizeof(D));
    }
    else
#endif
    dst = 0;
}

template<class DerivedLoader, class StorageClass>
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::convert_str_to_bool(uint32 /*field_pos*/, char const* /*src*/, bool& dst)
{
    dst = false;
}

template<class DerivedLoader, class StorageClass>
template<class S, class D>                                  // S source-type, D destination-type
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::default_fill(uint32 /*field_pos*/, S src, D& dst)
{
#if defined(__arm__)
    if (((unsigned) &dst) % sizeof(D)) {
       //The address is not aligned. Use memcpy to avoid ARM unaligned trap
       D converted(src);
       memcpy((void*) &dst, (void*) &converted, sizeof(D));
    }
    else
#endif
    dst = D(src);
}

template<class DerivedLoader, class StorageClass>
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::default_fill_to_str(uint32 /*field_pos*/, char const* /*src*/, char*& dst)
{
    dst = new char[1];
    *dst = 0;
}

template<class DerivedLoader, class StorageClass>
template<class V>                                           // V value-type
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::storeValue(V value, StorageClass& store, char* p, uint32 x, uint32& offset)
{
    DerivedLoader* subclass = (static_cast<DerivedLoader*>(this));
    switch (store.GetDstFormat(x))
    {
        case FT_LOGIC:
            subclass->convert_to_bool(x, value, *((bool*)(&p[offset])));
            offset += sizeof(bool);
            break;
        case FT_BYTE:
            subclass->convert(x, value, *((char*)(&p[offset])));
            offset += sizeof(char);
            break;
        case FT_INT:
        case FT_IND:
            subclass->convert(x, value, *((uint32*)(&p[offset])));
            offset += sizeof(uint32);
            break;
        case FT_FLOAT:
            subclass->convert(x, value, *((float*)(&p[offset])));
            offset += sizeof(float);
            break;
        case FT_STRING:
            subclass->convert_to_str(x, value, *((char**)(&p[offset])));
            offset += sizeof(char*);
            break;
        case FT_NA:
            subclass->default_fill(x, value, *((uint32*)(&p[offset])));
            offset += sizeof(uint32);
            break;
        case FT_NA_BYTE:
            subclass->default_fill(x, value, *((char*)(&p[offset])));
            offset += sizeof(char);
            break;
        case FT_NA_FLOAT:
            subclass->default_fill(x, value, *((float*)(&p[offset])));
            offset += sizeof(float);
            break;
        case FT_64BITINT:
            subclass->default_fill(x, value, *((uint64*)(&p[offset])));
            offset += sizeof(uint64);
            break;
        case FT_SORT:
            assert(false && "SQL storage not have sort field types");
            break;
        default:
            assert(false && "unknown format character");
            break;
    }
}

template<class DerivedLoader, class StorageClass>
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::storeValue(char const* value, StorageClass& store, char* p, uint32 x, uint32& offset)
{
    DerivedLoader* subclass = (static_cast<DerivedLoader*>(this));
    switch (store.GetDstFormat(x))
    {
        case FT_LOGIC:
            subclass->convert_str_to_bool(x, value, *((bool*)(&p[offset])));
            offset += sizeof(bool);
            break;
        case FT_BYTE:
            subclass->convert_from_str(x, value, *((char*)(&p[offset])));
            offset += sizeof(char);
            break;
        case FT_INT:
        case FT_IND:
            subclass->convert_from_str(x, value, *((uint32*)(&p[offset])));
            offset += sizeof(uint32);
            break;
        case FT_FLOAT:
            subclass->convert_from_str(x, value, *((float*)(&p[offset])));
            offset += sizeof(float);
            break;
        case FT_STRING:
            subclass->convert_str_to_str(x, value, *((char**)(&p[offset])));
            offset += sizeof(char*);
            break;
        case FT_NA_POINTER:
            subclass->default_fill_to_str(x, value, *((char**)(&p[offset])));
            offset += sizeof(char*);
            break;
        case FT_64BITINT:
            subclass->convert_from_str(x, value, *((uint64*)(&p[offset])));
            offset += sizeof(uint64);
            break;
        case FT_SORT:
            assert(false && "SQL storage not have sort field types");
            break;
        default:
            assert(false && "unknown format character");
            break;
    }
}

template<class DerivedLoader, class StorageClass>
void SQLStorageLoaderBase<DerivedLoader, StorageClass>::Load(StorageClass& store, bool error_at_empty /*= true*/)
{
    QueryResult* result = WorldDatabase.PQuery("SHOW COLUMNS FROM %s", store.GetTableName());
    if (!result)
    {
        sLog.outError("Error loading %s table (not exist?)\n", store.GetTableName());
        Log::WaitBeforeContinueIfNeed();
        exit(1);                                            // Stop server at loading non exited table or not accessable table
    }

    std::vector<std::string> colNameList;
    colNameList.reserve(result->GetRowCount());
    do
    {
        Field* fields = result->Fetch();
        colNameList.push_back(fields[0].GetString());
    } while (result->NextRow());

    delete result;

    int32 indexPos = -1;
    std::string indexName = store.EntryFieldName();
    if (indexName.empty())
    {
        for (int32 i = 0; i < int32(store.GetDstFieldCount()); ++i)
        {
            auto format = store.GetSrcFormat(i);
            if (format == FT_IND || format == FT_SORT)
            {
                indexPos = i;
                break;
            }
        }

        if (indexPos >= 0)
        {
            if (indexPos >= colNameList.size())
            {
                sLog.outError("Error loading %s table, provided index position is greater than column number\n", store.GetTableName());
                Log::WaitBeforeContinueIfNeed();
                exit(1);
            }
            indexName = colNameList[indexPos];
        }
    }
    else
    {
        std::transform(indexName.begin(), indexName.end(), indexName.begin(), [](char c) { return std::tolower(c); });
        for (uint32 i = 0; i < colNameList.size(); ++i)
        {
            std::string colName = colNameList[i];
            std::transform(colName.begin(), colName.end(), colName.begin(), [](char c) { return std::tolower(c); });
            if (indexName == colName)
            {
                indexName = colNameList[i];
                indexPos = i;
                break;
            }
        }

        if (indexPos < 0)
        {
            sLog.outError("Error loading %s table (Entry field is not found in column name list)\n", store.GetTableName());
            Log::WaitBeforeContinueIfNeed();
            exit(1);
        }
    }

    Field* fields = nullptr;
    uint32 maxRecordId = 0;
    uint32 recordCount = 0;
    uint32 recordsize = 0;

    result = WorldDatabase.PQuery("SELECT COUNT(*) FROM %s", store.GetTableName());
    if (result)
    {
        recordCount = result[0][0].GetUInt32();
        delete result;
    }

    if (indexPos < 0)
    {
        maxRecordId = recordCount;
    }
    else
    {
        result = WorldDatabase.PQuery("SELECT MAX(%s) FROM %s", indexName.c_str(), store.GetTableName());
        if (!result)
        {
            sLog.outError("Error loading %s table (not exist?)\n", store.GetTableName());
            Log::WaitBeforeContinueIfNeed();
            exit(1);                                            // Stop server at loading non exited table or not accessable table
        }

        maxRecordId = (*result)[0].GetUInt32() + 1;
        delete result;
    }

    result = WorldDatabase.PQuery("SELECT * FROM %s", store.GetTableName());
    if (!result)
    {
        if (error_at_empty)
            sLog.outError("%s table is empty!\n", store.GetTableName());
        else
            sLog.outString("%s table is empty!\n", store.GetTableName());

        recordCount = 0;
        maxRecordId = 0;
        return;
    }

    if (store.GetSrcFieldCount() != result->GetFieldCount())
    {
        recordCount = 0;
        sLog.outError("Error in %s table, probably sql file format was updated (there should be %d fields in sql).\n", store.GetTableName(), store.GetSrcFieldCount());
        delete result;
        Log::WaitBeforeContinueIfNeed();
        exit(1);                                            // Stop server at loading broken or non-compatible table.
    }

    // get struct size
    uint32 offset = 0;
    for (uint32 x = 0; x < store.GetDstFieldCount(); ++x)
    {
        switch (store.GetDstFormat(x))
        {
            case FT_LOGIC:
                recordsize += sizeof(bool);   break;
            case FT_BYTE:
                recordsize += sizeof(char);   break;
            case FT_INT:
            case FT_IND:
                recordsize += sizeof(uint32); break;
            case FT_FLOAT:
                recordsize += sizeof(float);  break;
            case FT_STRING:
                recordsize += sizeof(char*);  break;
            case FT_NA:
                recordsize += sizeof(uint32); break;
            case FT_NA_BYTE:
                recordsize += sizeof(char);   break;
            case FT_NA_FLOAT:
                recordsize += sizeof(float);  break;
            case FT_NA_POINTER:
                recordsize += sizeof(char*);  break;
            case FT_64BITINT:
                recordsize += sizeof(uint64);  break;
            case FT_SORT:
                break;
            default:
                assert(false && "unknown format character");
                break;
        }
    }

    // Prepare data storage and lookup storage
    store.prepareToLoad(maxRecordId, recordCount, recordsize);

    uint32 generatedId = 0;
    BarGoLink bar(recordCount);
    do
    {
        fields = result->Fetch();
        bar.step();

        uint32 id = 0;
        if (indexPos < 0)
            id = generatedId++;
        else
            id = fields[indexPos].GetUInt32();

        char* record = store.createRecord(id);
        offset = 0;

        // dependend on dest-size
        // iterate two indexes: x over dest, y over source
        //                      y++ If and only If x != FT_NA*
        //                      x++ If and only If a value is stored
        for (uint32 x = 0, y = 0; x < store.GetDstFieldCount();)
        {
            switch (store.GetDstFormat(x))
            {
                // For default fill continue and do not increase y
                case FT_NA:         storeValue((uint32)0, store, record, x, offset);         ++x; continue;
                case FT_NA_BYTE:    storeValue((char)0, store, record, x, offset);           ++x; continue;
                case FT_NA_FLOAT:   storeValue((float)0.0f, store, record, x, offset);       ++x; continue;
                case FT_NA_POINTER: storeValue((char const*)nullptr, store, record, x, offset); ++x; continue;
                default:
                    break;
            }

            // It is required that the input has at least as many columns set as the output requires
            if (y >= store.GetSrcFieldCount())
                assert(false && "SQL storage has too few columns!");

            switch (store.GetSrcFormat(y))
            {
                case FT_LOGIC:  storeValue((bool)(fields[y].GetUInt32() > 0), store, record, x, offset);  ++x; break;
                case FT_BYTE:   storeValue((char)fields[y].GetUInt8(), store, record, x, offset);         ++x; break;
                case FT_IND:
                case FT_INT:    storeValue((uint32)fields[y].GetUInt32(), store, record, x, offset);      ++x; break;
                case FT_FLOAT:  storeValue((float)fields[y].GetFloat(), store, record, x, offset);        ++x; break;
                case FT_STRING: storeValue((char const*)fields[y].GetString(), store, record, x, offset); ++x; break;
                case FT_64BITINT: storeValue(fields[y].GetUInt64(), store, record, x, offset);            ++x; break;
                case FT_SORT:
                    ++x;
                    break;

                case FT_NA:
                case FT_NA_BYTE:
                case FT_NA_FLOAT:
                    // Do Not increase x
                    break;
                case FT_NA_POINTER:
                    assert(false && "SQL storage not have sort or pointer field types");
                    break;
                default:
                    assert(false && "unknown format character");
            }
            ++y;
        }
    }
    while (result->NextRow());

    delete result;
}


// -----------------------------------  SQLStorage  -------------------------------------------- //
template<typename ST>
void SQLStorage<ST>::EraseEntry(uint32 id)
{
    m_Index[id] = nullptr;
}

template<typename ST>
void SQLStorage<ST>::Free()
{
    SQLStorageBase<ST>::Free();
    delete[] m_Index;
    m_Index = nullptr;
}

template<typename ST>
void SQLStorage<ST>::Load(bool error_at_empty /*= true*/)
{
    SQLStorageLoader<ST> loader;
    loader.Load(*this, error_at_empty);
}

template<typename ST>
SQLStorage<ST>::SQLStorage(const char* fmt, const char* sqlname)
{
    SQLStorage<ST>::Initialize(sqlname, "",fmt, fmt);
    m_Index = nullptr;
}

template<typename ST>
SQLStorage<ST>::SQLStorage(const char* fmt, const char* _entry_field, const char* sqlname)
{
    SQLStorage<ST>::Initialize(sqlname, _entry_field, fmt, fmt);
    m_Index = nullptr;
}

template<typename ST>
SQLStorage<ST>::SQLStorage(const char* src_fmt, const char* dst_fmt, const char* _entry_field, const char* sqlname)
{
    SQLStorage<ST>::Initialize(sqlname, _entry_field, src_fmt, dst_fmt);
    m_Index = nullptr;
}

template<typename ST>
void SQLStorage<ST>::prepareToLoad(uint32 maxRecordId, uint32 recordCount, uint32 recordSize)
{
    // Clear (possible) old data and old index array
    Free();

    // Set index array
    m_Index = new char* [maxRecordId];
    memset(m_Index, 0, maxRecordId * sizeof(char*));

    SQLStorageBase<ST>::prepareToLoad(maxRecordId, recordCount, recordSize);
}

// -----------------------------------  SQLStorageBase  ---------------------------------------- //
template<typename ST>
SQLStorageBase<ST>::SQLStorageBase() :
    m_tableName(nullptr),
    m_entry_field(nullptr),
    m_src_format(nullptr),
    m_dst_format(nullptr),
    m_dstFieldCount(0),
    m_srcFieldCount(0),
    m_recordCount(0),
    m_maxEntry(0),
    m_recordSize(0),
    m_data(nullptr)
{}

template<typename ST>
void SQLStorageBase<ST>::Initialize(const char* tableName, const char* entry_field, const char* src_format, const char* dst_format)
{
    m_tableName = tableName;
    m_entry_field = entry_field;
    m_src_format = src_format;
    m_dst_format = dst_format;

    m_srcFieldCount = strlen(m_src_format);
    m_dstFieldCount = strlen(m_dst_format);
}

template<typename ST>
char* SQLStorageBase<ST>::createRecord(uint32 recordId)
{
    char* newRecord = &m_data[m_recordCount * m_recordSize];
    ++m_recordCount;

    JustCreatedRecord(recordId, newRecord);
    return newRecord;
}

template<typename ST>
void SQLStorageBase<ST>::prepareToLoad(uint32 maxEntry, uint32 recordCount, uint32 recordSize)
{
    m_maxEntry = maxEntry;
    m_recordSize = recordSize;

    delete[] m_data;
    m_data = new char[recordCount * m_recordSize];
    memset(m_data, 0, recordCount * m_recordSize);

    m_recordCount = 0;
}

// Function to delete the data
template<typename ST>
void SQLStorageBase<ST>::Free()
{
    if (!m_data)
        return;

    uint32 offset = 0;
    for (uint32 x = 0; x < m_dstFieldCount; ++x)
    {
        switch (m_dst_format[x])
        {
            case FT_LOGIC:
                offset += sizeof(bool);
                break;
            case FT_STRING:
            {
                for (uint32 recordItr = 0; recordItr < m_recordCount; ++recordItr)
                    delete[] * (char**)((char*)(m_data + (recordItr * m_recordSize)) + offset);

                offset += sizeof(char*);
                break;
            }
            case FT_NA:
            case FT_IND:
            case FT_INT:
                offset += sizeof(uint32);
                break;
            case FT_BYTE:
            case FT_NA_BYTE:
                offset += sizeof(char);
                break;
            case FT_FLOAT:
            case FT_NA_FLOAT:
                offset += sizeof(float);
                break;
            case FT_NA_POINTER:
                // TODO- possible (and small) memleak here possible
                offset += sizeof(char*);
                break;
            case FT_64BITINT:
                offset += sizeof(uint64);
                break;
            case FT_SORT:
                break;
            default:
                assert(false && "unknown format character");
                break;
        }
    }
    delete[] m_data;
    m_data = nullptr;
    m_recordCount = 0;
}

// -----------------------------------  SQLHashStorage  ---------------------------------------- //
template<typename ST>
void SQLHashStorage<ST>::Load()
{
    SQLHashStorageLoader<ST> loader;
    loader.Load(*this);
}

template<typename ST>
void SQLHashStorage<ST>::Free()
{
    SQLStorageBase<ST>::Free();
    m_indexMap.clear();
}

template<typename ST>
void SQLHashStorage<ST>::prepareToLoad(uint32 maxRecordId, uint32 recordCount, uint32 recordSize)
{
    // Clear (possible) old data and old index array
    Free();

    SQLStorageBase<ST>::prepareToLoad(maxRecordId, recordCount, recordSize);
}

template<typename ST>
void SQLHashStorage<ST>::EraseEntry(uint32 id)
{
    // do not erase from m_records
    RecordMap::iterator find = m_indexMap.find(id);
    if (find != m_indexMap.end())
        find->second = nullptr;
}

template<typename ST>
SQLHashStorage<ST>::SQLHashStorage(const char* fmt, const char* _entry_field, const char* sqlname)
{
    SQLHashStorage<ST>::Initialize(sqlname, _entry_field, fmt, fmt);
}

template<typename ST>
SQLHashStorage<ST>::SQLHashStorage(const char* src_fmt, const char* dst_fmt, const char* _entry_field, const char* sqlname)
{
    SQLHashStorage<ST>::Initialize(sqlname, _entry_field, src_fmt, dst_fmt);
}

// -----------------------------------  SQLMultiStorage  --------------------------------------- //
template<typename ST>
void SQLMultiStorage<ST>::Load()
{
    SQLMultiStorageLoader<ST> loader;
    loader.Load(*this);
}

template<typename ST>
void SQLMultiStorage<ST>::Free()
{
    SQLStorageBase<ST>::Free();
    m_indexMultiMap.clear();
}

template<typename ST>
void SQLMultiStorage<ST>::prepareToLoad(uint32 maxRecordId, uint32 recordCount, uint32 recordSize)
{
    // Clear (possible) old data and old index array
    Free();

    SQLStorageBase<ST>::prepareToLoad(maxRecordId, recordCount, recordSize);
}

template<typename ST>
void SQLMultiStorage<ST>::EraseEntry(uint32 id)
{
    m_indexMultiMap.erase(id);
}

template<typename ST>
SQLMultiStorage<ST>::SQLMultiStorage(const char* fmt, const char* _entry_field, const char* sqlname)
{
    SQLMultiStorage<ST>::Initialize(sqlname, _entry_field, fmt, fmt);
}

template<typename ST>
SQLMultiStorage<ST>::SQLMultiStorage(const char* src_fmt, const char* dst_fmt, const char* _entry_field, const char* sqlname)
{
    SQLMultiStorage<ST>::Initialize(sqlname, _entry_field, src_fmt, dst_fmt);
}


#endif

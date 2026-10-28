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

#ifndef MANGOS_CALLBACK_H
#define MANGOS_CALLBACK_H

#include <concepts>
#include <memory>
#include <utility>

/// ---------- QUERY CALLBACKS -----------

class QueryResult;

namespace MaNGOS
{
    class IQueryCallback
    {
        public:

            virtual ~IQueryCallback() = default;
            virtual void Execute() = 0;
            virtual void SetResult(std::unique_ptr<QueryResult> queryResult) = 0;
    };

    /**
     * Callable needs to be a callable object (function object, pointer to function, reference
     * to function, pointer to member function, etc) that takes an std::unique_ptr<QueryResult>
     * or a pointer to QueryResult as an argument and returns void. The caller can use std::bind
     * to create such a callable object and bind any other required arguments for the actual callback.
     */
    template <typename Callable>
    requires(std::invocable<Callable&, QueryResult*> ||
             std::invocable<Callable&, std::unique_ptr<QueryResult>>)
    class QueryCallback : public IQueryCallback
    {
        public:

            QueryCallback(Callable&& callback)
            : m_Callback(std::forward<Callable>(callback))
            , m_QueryResult()
            {
            }

            void Execute() override
            {
                if constexpr (std::invocable<Callable&, QueryResult*>)
                {
                    m_Callback(m_QueryResult.release());
                }
                else
                {
                    m_Callback(std::move(m_QueryResult));
                }
            }

            void SetResult(std::unique_ptr<QueryResult> queryResult) override
            {
                m_QueryResult = std::move(queryResult);
            }

        private:

            Callable m_Callback;
            std::unique_ptr<QueryResult> m_QueryResult;
    };
}

#endif

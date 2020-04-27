/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2020  Vladimir Golovnev <glassez@yandex.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 */

#include "customstorage.h"

CustomStorage::CustomStorage(const lt::storage_params &params, lt::file_pool &filePool)
    : lt::storage_interface {params.files}
    , m_defaultStorage {std::make_unique<lt::default_storage>(params, filePool)}
{
}

CustomStorage::~CustomStorage()
{
}


void CustomStorage::initialize(lt::storage_error &ec)
{
    m_defaultStorage->initialize(ec);
}

int CustomStorage::readv(lt::span<const lt::iovec_t> bufs, lt::piece_index_t piece
                   , int offset, lt::open_mode_t flags, lt::storage_error &ec)
{
    return m_defaultStorage->readv(bufs, piece, offset, flags, ec);
}

int CustomStorage::writev(lt::span<const lt::iovec_t> bufs, lt::piece_index_t piece
                    , int offset, lt::open_mode_t flags, lt::storage_error &ec)
{
    return m_defaultStorage->writev(bufs, piece, offset, flags, ec);
}

bool CustomStorage::has_any_file(lt::storage_error &ec)
{
    return m_defaultStorage->has_any_file(ec);
}

void CustomStorage::set_file_priority(lt::aux::vector<lt::download_priority_t, lt::file_index_t> &prio, lt::storage_error &ec)
{
    m_defaultStorage->set_file_priority(prio, ec);
}

lt::status_t CustomStorage::move_storage(const std::string &save_path, lt::move_flags_t flags, lt::storage_error &ec)
{
    return m_defaultStorage->move_storage(save_path, flags, ec);
}

bool CustomStorage::verify_resume_data(const lt::add_torrent_params &rd, const lt::aux::vector<std::string, lt::file_index_t> &links, lt::storage_error &ec)
{
    return m_defaultStorage->verify_resume_data(rd, links, ec);
}

void CustomStorage::release_files(lt::storage_error &ec)
{
    m_defaultStorage->release_files(ec);
}

void CustomStorage::rename_file(lt::file_index_t index, const std::string &new_filename, lt::storage_error &ec)
{
    m_defaultStorage->rename_file(index, new_filename, ec);
}

void CustomStorage::delete_files(lt::remove_flags_t options, lt::storage_error &ec)
{
    m_defaultStorage->delete_files(options, ec);
}

bool CustomStorage::tick()
{
    return m_defaultStorage->tick();
}

lt::storage_interface *customStorageConstructor(const lt::storage_params &params, lt::file_pool &pool)
{
    return new CustomStorage(params, pool);
}

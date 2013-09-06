"""
Wrap protocol constants.
"""

__author__     = "Jon Bringhurst <jon@bringhurst.org>"
__copyright__  = "Copyright 2013 Los Alamos National Security, LLC."
__license__    = "Apache License, Version 2.0"

import msgpack
import struct

class HavenProtocol():

    # Overall protocol version.
    HVN_PROTOCOL_VERSION                 = 0x01
    HVN_PROTOCOL_MAGIC                   = 0xDECAFBAD

    # Client request msg types.
    HVN_PROTO_MSG_TYPE_APPEND            = 0x01
    HVN_PROTO_MSG_TYPE_CONNECT           = 0x03
    HVN_PROTO_MSG_TYPE_CONTROL           = 0x02
    HVN_PROTO_MSG_TYPE_DATA              = 0x06
    HVN_PROTO_MSG_TYPE_DISCOVER          = 0x07
    HVN_PROTO_MSG_TYPE_HEARTBEAT         = 0x05
    HVN_PROTO_MSG_TYPE_VOTE              = 0x04

    # Server response msg types.
    HVN_PROTO_MSG_TYPE_APPEND_R          = 0x0C
    HVN_PROTO_MSG_TYPE_CONNECT_R         = 0x0D
    HVN_PROTO_MSG_TYPE_CONTROL_R         = 0x0F
    HVN_PROTO_MSG_TYPE_DATA_R            = 0x0E
    HVN_PROTO_MSG_TYPE_DISCOVER_R        = 0x0A
    HVN_PROTO_MSG_TYPE_HEARTBEAT_R       = 0x0B
    HVN_PROTO_MSG_TYPE_VOTE_R            = 0x09

    # Data client requests.
    HVN_CLNT_PROTO_DATA_VERB_READ        = 0x01
    HVN_CLNT_PROTO_DATA_VERB_WRITE       = 0x03
    HVN_CLNT_PROTO_DATA_VERB_DELETE      = 0x06
    HVN_CLNT_PROTO_DATA_VERB_WATCH       = 0x07
    HVN_CLNT_PROTO_DATA_VERB_UNWATCH     = 0x05
    HVN_CLNT_PROTO_DATA_TRANSACTION      = 0x04

    # Data client request modes.
    HVN_CLNT_PROTO_DATA_MODE_RW          = 0x0C
    HVN_CLNT_PROTO_DATA_MODE_RO          = 0x0D
    HVN_CLNT_PROTO_DATA_MODE_RB          = 0x1D
    HVN_CLNT_PROTO_DATA_MODE_RT          = 0x1C

    # Data server responses.
    HVN_CLNT_PROTO_DATA_R_OK             = 0x14
    HVN_CLNT_PROTO_DATA_R_ERR            = 0x34

    # Control client requests.
    HVN_PROTO_CTRL_ATTACH_APPEND         = 0x01
    HVN_PROTO_CTRL_ATTACH_DATA           = 0x03
    HVN_PROTO_CTRL_ATTACH_VOTE           = 0x02
    HVN_PROTO_CTRL_DESTROY               = 0x06
    HVN_PROTO_CTRL_EXIT                  = 0x07
    HVN_PROTO_CTRL_FOLLOWER              = 0x05
    HVN_PROTO_CTRL_LEADER                = 0x04
    HVN_PROTO_CTRL_LOCATION              = 0x0C
    HVN_PROTO_CTRL_PROXY                 = 0x0D
    HVN_PROTO_CTRL_ROUTER                = 0x0F

    # Control server responses.
    HVN_PROTO_CTRL_R_OK                  = 0x0E
    HVN_PROTO_CTRL_R_ERR                 = 0x1E
    HVN_PROTO_CTRL_R_NOT_FOUND           = 0x1F

    def send_connect(self, conn):
        msg = msgpack.packb([
            HavenProtocol.HVN_PROTO_MSG_TYPE_CONNECT,
            HavenProtocol.HVN_PROTOCOL_MAGIC,
            HavenProtocol.HVN_PROTOCOL_VERSION
        ])
        self.send(msg, conn)

    def recv_connect(self, conn):
        msg = self.recv(conn)
        print("Contents of received connect response message: " + \
            str(msgpack.unpackb(msg)))

    def send_control(self, conn, action, uuid=None, path=None):
        msg = msgpack.packb([
            HavenProtocol.HVN_PROTO_MSG_TYPE_CONTROL,
            action,
            uuid,
            path
        ])
        self.send(msg, conn)

    def recv_control(self, conn):
        msg = self.recv(conn)
        print("Contents of received control response message: " + \
            str(msgpack.unpackb(msg)))

    def send_data(self, conn, verb, mode, earliest, latest, key, value):
        msg = msgpack.packb([
            HavenProtocol.HVN_PROTO_MSG_TYPE_DATA,
            verb,
            mode,
            [earliest, latest],
            key,
            value
        ])
        self.send(msg, conn)

    def recv_data(self, conn):
        msg = self.recv(conn)
        print("Contents of received data response message: " + \
            str(msgpack.unpackb(msg)))

    def send_discover(self, conn):
        print "not implemented"

    def send_heartbeat(self, conn):
        print "not implemented"

    def recv(self, conn):
        msg_len = struct.unpack("<L", conn.recv(4))[0]
        msg = conn.recv(msg_len)
        print("Received message of `{0}' (`{1}+4' bytes).".format(repr(msg), len(msg)))
        return msg

    def send(self, msg, conn):
        print("Sending message `{0}' (`{1}+4' bytes).".format(repr(msg), len(msg)))
        conn.send(struct.pack('!i', len(msg)))
        conn.send(msg)

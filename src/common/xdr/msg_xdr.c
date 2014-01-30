/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "msg.h"

bool_t
xdr_HVN_msg_type (XDR *xdrs, HVN_msg_type *objp)
{
	register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_replica_info (XDR *xdrs, HVN_replica_info *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_opaque (xdrs, objp->uuid, 16))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->port))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->address, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_bootstrap_t (XDR *xdrs, HVN_msg_bootstrap_t *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_HVN_msg_type (xdrs, &objp->type))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->uuid, 16))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->port))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->address, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_resp_bootstrap_t (XDR *xdrs, HVN_msg_resp_bootstrap_t *objp)
{
	register int32_t *buf;

	 if (!xdr_HVN_msg_type (xdrs, &objp->type))
		 return FALSE;
	 if (!xdr_bool (xdrs, &objp->success))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->known_replicas.known_replicas_val, (u_int *) &objp->known_replicas.known_replicas_len, ~0,
		sizeof (HVN_replica_info), (xdrproc_t) xdr_HVN_replica_info))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_connect_t (XDR *xdrs, HVN_msg_connect_t *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_opaque (xdrs, objp->magic, 4))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->api_version, 4))
		 return FALSE;
	 if (!xdr_HVN_msg_type (xdrs, &objp->type))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_resp_connect_t (XDR *xdrs, HVN_msg_resp_connect_t *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_opaque (xdrs, objp->api_version, 4))
		 return FALSE;
	 if (!xdr_HVN_msg_type (xdrs, &objp->type))
		 return FALSE;
	 if (!xdr_bool (xdrs, &objp->success))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_consensus_t (XDR *xdrs, HVN_msg_consensus_t *objp)
{
	register int32_t *buf;

	int i;

	if (xdrs->x_op == XDR_ENCODE) {
		 if (!xdr_HVN_msg_type_e (xdrs, &objp->type))
			 return FALSE;
		 if (!xdr_bool (xdrs, &objp->is_vote))
			 return FALSE;
		 if (!xdr_opaque (xdrs, objp->uuid_id, 16))
			 return FALSE;
		buf = XDR_INLINE (xdrs, 4 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_u_long (xdrs, &objp->term))
				 return FALSE;
			 if (!xdr_u_long (xdrs, &objp->log_index))
				 return FALSE;
			 if (!xdr_u_long (xdrs, &objp->log_term))
				 return FALSE;
			 if (!xdr_u_long (xdrs, &objp->commit_index))
				 return FALSE;

		} else {
		IXDR_PUT_U_LONG(buf, objp->term);
		IXDR_PUT_U_LONG(buf, objp->log_index);
		IXDR_PUT_U_LONG(buf, objp->log_term);
		IXDR_PUT_U_LONG(buf, objp->commit_index);
		}
		 if (!xdr_pointer (xdrs, (char **)&objp->log_entries, sizeof (UT_array), (xdrproc_t) xdr_UT_array))
			 return FALSE;
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		 if (!xdr_HVN_msg_type_e (xdrs, &objp->type))
			 return FALSE;
		 if (!xdr_bool (xdrs, &objp->is_vote))
			 return FALSE;
		 if (!xdr_opaque (xdrs, objp->uuid_id, 16))
			 return FALSE;
		buf = XDR_INLINE (xdrs, 4 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_u_long (xdrs, &objp->term))
				 return FALSE;
			 if (!xdr_u_long (xdrs, &objp->log_index))
				 return FALSE;
			 if (!xdr_u_long (xdrs, &objp->log_term))
				 return FALSE;
			 if (!xdr_u_long (xdrs, &objp->commit_index))
				 return FALSE;

		} else {
		objp->term = IXDR_GET_U_LONG(buf);
		objp->log_index = IXDR_GET_U_LONG(buf);
		objp->log_term = IXDR_GET_U_LONG(buf);
		objp->commit_index = IXDR_GET_U_LONG(buf);
		}
		 if (!xdr_pointer (xdrs, (char **)&objp->log_entries, sizeof (UT_array), (xdrproc_t) xdr_UT_array))
			 return FALSE;
	 return TRUE;
	}

	 if (!xdr_HVN_msg_type_e (xdrs, &objp->type))
		 return FALSE;
	 if (!xdr_bool (xdrs, &objp->is_vote))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->uuid_id, 16))
		 return FALSE;
	 if (!xdr_u_long (xdrs, &objp->term))
		 return FALSE;
	 if (!xdr_u_long (xdrs, &objp->log_index))
		 return FALSE;
	 if (!xdr_u_long (xdrs, &objp->log_term))
		 return FALSE;
	 if (!xdr_u_long (xdrs, &objp->commit_index))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->log_entries, sizeof (UT_array), (xdrproc_t) xdr_UT_array))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_resp_consensus_t (XDR *xdrs, HVN_msg_resp_consensus_t *objp)
{
	register int32_t *buf;

	 if (!xdr_u_long (xdrs, &objp->term))
		 return FALSE;
	 if (!xdr_bool (xdrs, &objp->success))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_control_action_type (XDR *xdrs, HVN_msg_control_action_type *objp)
{
	register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_control_t (XDR *xdrs, HVN_msg_control_t *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_HVN_msg_control_action_type (xdrs, &objp->action))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->uuid, 16))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_resp_control_t (XDR *xdrs, HVN_msg_resp_control_t *objp)
{
	register int32_t *buf;

	 if (!xdr_bool (xdrs, &objp->success))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_data_transaction (XDR *xdrs, HVN_msg_data_transaction *objp)
{
	register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_data_verb (XDR *xdrs, HVN_msg_data_verb *objp)
{
	register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_data_mode (XDR *xdrs, HVN_msg_data_mode *objp)
{
	register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_data_op_t (XDR *xdrs, HVN_msg_data_op_t *objp)
{
	register int32_t *buf;

	 if (!xdr_HVN_msg_data_verb (xdrs, &objp->verb))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->data.data_val, (u_int *) &objp->data.data_len, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_data_t (XDR *xdrs, HVN_msg_data_t *objp)
{
	register int32_t *buf;

	 if (!xdr_HVN_msg_data_mode (xdrs, &objp->mode))
		 return FALSE;
	 if (!xdr_HVN_msg_data_transaction (xdrs, &objp->transaction))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->ops.ops_val, (u_int *) &objp->ops.ops_len, ~0,
		sizeof (HVN_msg_data_op_t), (xdrproc_t) xdr_HVN_msg_data_op_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_HVN_msg_resp_data_t (XDR *xdrs, HVN_msg_resp_data_t *objp)
{
	register int32_t *buf;

	 if (!xdr_bool (xdrs, &objp->success))
		 return FALSE;
	return TRUE;
}
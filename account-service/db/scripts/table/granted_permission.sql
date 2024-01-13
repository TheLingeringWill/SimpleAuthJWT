DROP TABLE IF EXISTS granted_permission;

CREATE TABLE granted_permission
(
  /* ID fields */
  role_id BIGINT,
  permission_id BIGINT,

  /* Mandatory fields */

    /* Optional fields */

    /* Primary keys constraints */

    /* Foreign keys constraints */
  CONSTRAINT granted_permission_role_fkey FOREIGN KEY (role_id)
  REFERENCES role (id),

  CONSTRAINT granted_permission_fkey FOREIGN KEY (permission_id)
  REFERENCES permission (id)

/* Uniques constraints */
);

/* For one-to-one relation ship constraints */

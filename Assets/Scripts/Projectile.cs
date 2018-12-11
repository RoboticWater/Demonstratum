using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Projectile : MonoBehaviour
{
	public Vector3 dir;
	public float speed;
	public float life;
	public float damage;

	void Update()
	{
		life -= Time.deltaTime;
		transform.position += dir * speed * Time.deltaTime;
		if (life <= 0)
		{
			Destroy(this.gameObject);
		}
	}

	private void OnTriggerEnter(Collider other)
	{
		Player p = other.gameObject.GetComponent<Player>();
		if (p != null)
		{
			p.damage(damage);
		}
		Destroy(this.gameObject);
	}
}

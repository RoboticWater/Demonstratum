using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEditor;

public class Guard : MonoBehaviour
{

	public float minWaitTime;
	public float maxWaitTime;
	public float minLookTime;
	public float maxLookTime;
	public float minLookDir;
	public float maxLookDir;
	[Range(0.0f, 50.0f)] public float searchRadius;
	[Range(0.0f, 2.0f)] public float moveError;
	public float lookSpeed;
	public AnimationCurve lookCurve;
	[Range(0.0f, 50.0f)]
	public float viewDistance;
	[Range(0.0f, 180.0f)]
	public float viewAngle;
	public float sightLengthError;
	[Range(0.0f, 50.0f)]
	public float attackDist;
	public float fireRate;
	public float damage;
	public GameObject projectilePrefab;
	public float chaseViewDistance;
	public Color idleCol;
	public Color chaseCol;
	public bool passive;
	public Guard[] alertOthers;

	private NavMeshAgent agent;
	public HumanState state;
	public Vector3 searchPosition;
	private float waitTimer = 0.1f;
	private float lookTimer;
	private float sightTimer;
	private bool moving;
	private float lookTarget;
	private Light sight;
	private float fireTimer;
	[HideInInspector] public Vector3 lastPlayerPos;
	private Transform head;
	private bool moveToAttack = false;

	private IEnumerator lookRoutine;
	AudioSource glitchNoise;

	void Start()
	{
		agent = GetComponent<NavMeshAgent>();
		sight = GetComponentInChildren<Light>();
		searchPosition = transform.position;
		lookRoutine = look();
		sightTimer = sightLengthError;
		agent.SetDestination(transform.position);
		head = transform.Find("Head");
		glitchNoise = GetComponent<AudioSource>();
	}

	void Update()
	{
		switch (state)
		{
			case HumanState.Idle:
				break;
			case HumanState.Patrole:
				patrole();
				break;
			case HumanState.Chase:
				chase();
				break;
			case HumanState.Attack:
				attack();
				break;
		}
	}

	public void Alert(Vector3 playerPos)
	{
		if (state == HumanState.Patrole)
			searchPosition = Vector3.Lerp(transform.position, playerPos, 0.5f);
	}

	public void MoveToAttack()
	{
		state = HumanState.Chase;
	}

	public void goTo(Vector3 pos)
	{
		agent.SetDestination(pos);
	}

	void patrole()
	{
		if (playerInSight())
		{
			sightTimer += Time.deltaTime;
			if (sightTimer > sightLengthError)
			{
				foreach (Guard h in alertOthers)
				{
					h.MoveToAttack();
				}
				state = HumanState.Chase;
				sightTimer = 0;
				if (!glitchNoise.isPlaying)
				{
					glitchNoise.pitch = Random.Range(0.8f, 1.2f);
					glitchNoise.Play();
				}
			}
		}
		else
		{
			sightTimer = 0;
			sight.color = idleCol;
		}

		if (moving && Vector3.Distance(transform.position, agent.destination) < moveError)
		{
			moving = false;
		}
		else
		{
			if (searchRadius > 0)
				waitTimer -= Time.deltaTime;
			lookTimer -= Time.deltaTime;
			if (waitTimer <= 0)
			{
				StopCoroutine(lookRoutine);
				setRandomTarget();
				moving = true;
				waitTimer = Random.Range(minWaitTime, maxWaitTime);
			}
			if (lookTimer <= 0)
			{
				StopCoroutine(lookRoutine);
				lookRoutine = look();
				lookTarget += Random.Range(minLookDir, maxLookDir);
				lookTimer = Random.Range(minLookTime, maxLookTime);
				StartCoroutine(lookRoutine);
			}
		}
	}

	void chase()
	{
		if (passive)
		{
			state = HumanState.Patrole;
			return;
		}
		if (moveToAttack)
		{
			agent.SetDestination(lastPlayerPos);
			sight.color = chaseCol;
			if (Vector3.Distance(GameManager.instance.Player.transform.position, transform.position) < attackDist)
			{
				agent.isStopped = true;
				state = HumanState.Attack;
			}
			return;
		}
		Vector3 toPlayer = GameManager.instance.Player.transform.position - sight.transform.position;
		if (toPlayer.magnitude <= chaseViewDistance)
		{
			RaycastHit hit;
			if (Physics.Raycast(sight.transform.position, toPlayer, out hit, viewDistance))
			{
				if (hit.collider.gameObject.GetComponent<Player>() != null)
					lastPlayerPos = GameManager.instance.Player.transform.position;
				else
				{
					searchPosition = lastPlayerPos;
					state = HumanState.Patrole;
					return;
				}
			}
		}
		else
		{
			searchPosition = lastPlayerPos;
			state = HumanState.Patrole;
			return;
		}
		agent.SetDestination(lastPlayerPos);
		sight.color = chaseCol;
		if (Vector3.Distance(GameManager.instance.Player.transform.position, transform.position) < attackDist)
		{
			agent.isStopped = true;
			state = HumanState.Attack;
		}
	}

	private bool playerInSight()
	{
		Vector3 toPlayer = GameManager.instance.Player.transform.position - sight.transform.position;
		float angle = Vector2.Angle(new Vector2(toPlayer.x, toPlayer.z),
				new Vector2(transform.forward.x, transform.forward.z));
		bool inSight = false;
		if (angle < viewAngle && toPlayer.magnitude < viewDistance)
		{
			RaycastHit hit;
			if (Physics.Raycast(sight.transform.position, toPlayer, out hit, viewDistance))
			{
				inSight = hit.collider.gameObject.GetComponent<Player>() != null;
			}
		}
		return inSight;
	}

	void attack()
	{
		if (moveToAttack)
			moveToAttack = false;
		Vector3 direction = (GameManager.instance.Player.transform.position - transform.position).normalized;
		Quaternion lookRotation = Quaternion.LookRotation(new Vector3(direction.x, 0, direction.z));
		transform.rotation = Quaternion.Slerp(transform.rotation, lookRotation, Time.deltaTime * 12);

		Vector3 toPlayer = GameManager.instance.Player.transform.position - head.transform.position;
		if (toPlayer.magnitude > attackDist)
		{
			agent.SetDestination(GameManager.instance.Player.transform.position);
			agent.isStopped = false;
			state = HumanState.Chase;
			return;
		}
		else
		{
			RaycastHit hit;
			if (Physics.Raycast(head.transform.position, toPlayer, out hit, attackDist))
			{
				if (hit.collider.gameObject.GetComponent<Player>() == null)
				{
					agent.SetDestination(GameManager.instance.Player.transform.position);
					agent.isStopped = false;
					state = HumanState.Chase;
					return;
				}
			}
		}

		fireTimer -= Time.deltaTime;
		if (fireTimer <= 0)
		{
			fireTimer = fireRate;
			GameObject projectile = Instantiate(projectilePrefab);
			projectile.transform.position = head.transform.position + transform.forward * 0.5f;
			Projectile p = projectile.GetComponent<Projectile>();
			p.dir = GameManager.instance.Player.transform.position - head.transform.position;
			p.damage = damage;
		}
	}

	IEnumerator look()
	{
		float time = 0;
		float perc = 0;
		float lastTime = Time.realtimeSinceStartup;
		Quaternion curLook = transform.rotation;
		do
		{
			time += Time.realtimeSinceStartup - lastTime;
			lastTime = Time.realtimeSinceStartup;
			perc = Mathf.Clamp01(time / lookSpeed);

			transform.rotation = Quaternion.Lerp(curLook, Quaternion.Euler(curLook.eulerAngles.x, lookTarget, curLook.eulerAngles.z), lookCurve.Evaluate(perc));
			yield return null;
		} while (perc < 1);
	}

	void setRandomTarget()
	{
		Vector3 finalPosition = Vector3.zero;
		for (int i = 0; i < 1000 && finalPosition == Vector3.zero; i++)
		{
			Vector3 randomDirection = searchPosition + Random.insideUnitSphere * searchRadius;
			NavMeshHit hit;
			if (NavMesh.SamplePosition(randomDirection, out hit, searchRadius, 1))
			{
				finalPosition = hit.position;
			}
		}
		agent.SetDestination(finalPosition);
	}
}

public enum HumanState
{
	Idle, Patrole, Chase, Attack
}

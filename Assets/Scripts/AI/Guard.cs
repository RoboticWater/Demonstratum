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
	public GuardState state;
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
		// Runs fuction corresponding to current state
		switch (state)
		{
			case GuardState.Idle:
				break;
			case GuardState.Patrole:
				patrole();
				break;
			case GuardState.Chase:
				chase();
				break;
			case GuardState.Attack:
				attack();
				break;
		}
	}

	/// <summary>
	/// Alert this guard to search a position. This guard will then set their search position to that location and start searching there
	/// </summary>
	/// <param name="playerPos">The position of the player (it can be any position, but it'll probably be the player)</param>
	public void Alert(Vector3 playerPos)
	{
		if (state == GuardState.Patrole)
			searchPosition = Vector3.Lerp(transform.position, playerPos, 0.5f);
	}

	/// <summary>
	/// Set this guard to immedately chase the player. The Guard will automatically be given their position
	/// </summary>
	public void MoveToChase()
	{
		lastPlayerPos = GameManager.instance.Player.transform.position;
		state = GuardState.Chase;
	}

	/// <summary>
	/// Tell this guard to go to a specific location. This command will be overwritten if the guard is chasing or beings to chase the player.
	/// </summary>
	/// <param name="pos"></param>
	public void goTo(Vector3 pos)
	{
		agent.SetDestination(pos);
	}

	/// <summary>
	/// The patrole loop:
	/// The guard will walk randomly to positions in their search area and look around them.
	/// When the player is in sight, they will play an alert noise, alert any guards that are connected to it (alertOthers), and set its state to chase
	/// </summary>
	void patrole()
	{
		if (playerInSight())						// if the player is in sight
		{
			sightTimer += Time.deltaTime;			// sightTimer gives the player some wiggle room if spotted
			if (sightTimer > sightLengthError)		// if the player is in sight for long enough, they are officially seen
			{
				foreach (Guard h in alertOthers)	// alert connected guards
				{
					h.MoveToChase();
				}
				state = GuardState.Chase;			// set current state to chase
				sightTimer = 0;						// reset the sight timer for the next time you're in patrole
				if (!glitchNoise.isPlaying)			// if you aren't making an alert noise, do so
				{
					glitchNoise.pitch = Random.Range(0.8f, 1.2f);
					glitchNoise.Play();
				}
			}
		}
		else
		{
			sightTimer = 0;
			sight.color = idleCol;	// set your vision color to be the idle (safe) color
		}

		if (moving && Vector3.Distance(transform.position, agent.destination) < moveError)	// if you've moved close enough to your destination, allow yourself to find a new one
		{
			moving = false;
		}
		else
		{
			if (searchRadius > 0)				// if you have an area to search, decrement the wait timer so that you will eventually move positions
				waitTimer -= Time.deltaTime;
			lookTimer -= Time.deltaTime;		// decrement the look timer so you will eventually look another direction
			if (waitTimer <= 0) 				// if you have waited the allotted time, then move to another position and reset the timer
			{
				StopCoroutine(lookRoutine);		// make sure to stop the looking animation, so it's not awkwardly looking when it moves 
				setRandomTarget();
				moving = true;
				waitTimer = Random.Range(minWaitTime, maxWaitTime);
			}
			if (lookTimer <= 0)					// if you have waited long enough, aim the eyes in a different direction
			{									// this is done with a coroutine
				StopCoroutine(lookRoutine);		// make sure to stop looking if you already are (this is purely a precaution)
				lookRoutine = look();
				lookTarget += Random.Range(minLookDir, maxLookDir);
				lookTimer = Random.Range(minLookTime, maxLookTime);
				StartCoroutine(lookRoutine);
			}
		}
	}

	/// <summary>
	/// The chase loop:
	/// </summary>
	void chase()
	{
		if (passive)
		{
			state = GuardState.Patrole;
			return;
		}
		if (moveToAttack)
		{
			agent.SetDestination(lastPlayerPos);
			sight.color = chaseCol;
			if (Vector3.Distance(GameManager.instance.Player.transform.position, transform.position) < attackDist)
			{
				agent.isStopped = true;
				state = GuardState.Attack;
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
					state = GuardState.Patrole;
					return;
				}
			}
		}
		else
		{
			searchPosition = lastPlayerPos;
			state = GuardState.Patrole;
			return;
		}
		agent.SetDestination(lastPlayerPos);
		sight.color = chaseCol;
		if (Vector3.Distance(GameManager.instance.Player.transform.position, transform.position) < attackDist)
		{
			agent.isStopped = true;
			state = GuardState.Attack;
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
			state = GuardState.Chase;
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
					state = GuardState.Chase;
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

public enum GuardState
{
	Idle, Patrole, Chase, Attack
}

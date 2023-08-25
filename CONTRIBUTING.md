## Welcome to BitAlchemy contribution guide

First of all, let me thnk you for taking the time to contribute to this little pet project of mine. Any contribution you make will be deeply appreciated and I will make sure to provide proper credit to you whenever possible. Thank you!

### Contribution Guidelines

#### Did you spot a bug?
* **Ensure that the bug originates from BitAlchemy and not in some of its dependencies.** Like SDL2, SDL2_* or rapidxml.
* **Ensure that the bug is not already reported.** If it is already reported, then chances are me or other contributors are already trying to solve the issue.
* If you're unable to find an issue addressing the problem, then **open a new one.** Be sure to include **title and clear description**, as much information you can provide. Adding a **code sample** and/or error messages recieved will help the most.

#### Did you write a patch for a bug?
* Open a new Github Pull Request with the patch.
* Ensure the PR description clearly describes the problem (Or place a link to the issue if there is one) and describe the solutions
* Please make sure the PR follows the coding conventions described at the bottom of this page.

#### Do you wish to add/request new features for the library?
* Please open an issue with title and description briefly describing the new requested feature. And if you wish to add the feature yourself, then you may start coding.
* If you wish to contribute code, then open a Pull Request with title and description describing the new feature.
* Please make sure the PR follows the coding conventions described at the bottom of this page.

#### What about non-code contribution?
* Just open a PR. code documentations are always appreciated. Everything else, I'll decide to accept on a case-by-case basis.


### Coding Conventions used in this library.
* **Use tabs for indentation**. The width, you could define yourself so long as you remain consistent with its usage (1 tab per nested block).
* Use camel-casing when declaring names (variables, function names, class names)
	* Note that **functions/methods start with lowercase:**
		```
			void onEggsCooked(...) {
				...
	  		}
	
			void DemoScene::onCreate(...) {
	  			...
			}
	  
	  		template <typename T>
	  		constexpr float Vector2<t>::distance(...) {
	  			...
	  		}
  		```
	* And **Classes/Structs/Enums declartion start with uppercase:**
   		```
			class Entity {
	     		...
	     	};
	     	struct Sequence {
	     		...
	     	};
	     	enum ComponentID {
	     		...
	     	}
     	```
 	* **An exception to this rule are constants:** which are all **uppercase and use underscores**
    	```
     		bool IS_A_VALID_CONSTANT = true;

     		enum CollisionLayer {
     			NO_LAYER = 0, BACKGROUND, TILE_1, TILE_2, OBJECT_1, OBJECT_2, PLAYER_PROJECTILE, NPC_PROJECTILE, ...
     		};
     	```
* For **member variables** of classes/structs, we use prefixes:
  	* **`s_`** for static member vairables: `s_resourcesLoaded = false;`
  	* **`k_`** for constants: `float k_PI = 3.1415926535f;`
  	* **`sk_`** for static constants: `float sk_SPAM_TO_EGG_RATIO = 2.2321f;`
  	* **`m_`** for all other member variables: `int m_eggNumbers = 0;`


That is all. Once again, thank you for your contribution!

JavinalCharles
